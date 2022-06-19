#include <windows.h>
#include <mmsystem.h>
#include "i_midi.h"

extern HINSTANCE hInst;

MIDIPROPTIMEDIV mptd;                                    // Timing variables
MIDIPROPTEMPO   mpt;                                     // Timing variables
HANDLE    hevent;                                        // Event handle used for synchronization with MIDI playback
UINT imidiOutput, imidiTonebank, imidiTonebankDrum;      // MIDI device IDs
DWORD     imidiCur, imidiMax;                            // MIDI device IDs
MIDIHDR   mhOutput, mhTonebank, mhTonebankDrum;          // MIDIHDR structures
HMIDIOUT  hmo, hmoDrum;                                  // MIDI device handles
HMIDISTRM hms;                                           // MIDI device handle
WORD      td;                                            // Time division variables

BYTE      *pbTonebankNew     = NULL;                     // Pointers to new copies of data used
BYTE      *pbTonebankDrumNew = NULL;                     // Pointers to new copies of data used
BOOL      fFoundOutput       = FALSE;
BOOL      fFoundTonebank     = FALSE;
BOOL      fTemp              = TRUE;

int g_looping = 0;
int g_playing = 0;

extern int 		snd_MusicVolume; 
int 		old_snd_MusicVolume = 15; 



char szCurrentMidi[MAX_PATH+1];

BYTE* AllocAligned(DWORD cb, DWORD cbAlign);
void FreeAligned(BYTE *pbyData);
void FreeSequence(BYTE *pbSequence);
BOOL notagain = 0;
int MidiInit()
{
    //if( notagain ) return 0;
    //notagain = 1;

    // Initialize the MIDIHDR structures
    memset(&mhTonebank, 0, sizeof(mhTonebank));
    memset(&mhTonebankDrum, 0, sizeof(mhTonebankDrum));


    // Create the event handle used for synchronization with MIDI playback
    hevent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (hevent == NULL) return 0;

    // Query the MIDI subsystem for the number of MIDI devices
    // NOTE: On Dreamcast, this will always be 32 -- 16 sequencing devices, and
    //       16 devices used to manage the tonebank slots.  Thus, this and the code
    //       immediately following (to actually identify the streaming and tonebank
    //       MIDI devices) is optional for Dreamcast-only applications.

    imidiMax = midiOutGetNumDevs();
    if (imidiMax == 0) { MidiDone(); return 0; }

    // Enumerate the devices, finding the first sequencing device and the first tonebank device
    for (imidiCur = 0; (!fFoundOutput || !fFoundTonebank) && (imidiCur < imidiMax); imidiCur++)
    {
        MIDIOUTCAPS moc;

        // Query the MIDI subsystem for the device capabilities
        if( midiOutGetDevCaps(imidiCur, &moc, sizeof(moc)) != MMSYSERR_NOERROR ) { MidiDone(); return 0; }

        // Check to see if this device understands MIDI sequences
        if (moc.dwSupport & MIDICAPS_STREAM)
        {
            // If it does, and we still need one of those, remember it
            if (!fFoundOutput)
            {
                imidiOutput = imidiCur;
                fFoundOutput = TRUE;
            }
        }
        else
        {
            // If it does, and we still need a tonebank device, remember it
            if (!fFoundTonebank)
            {
                imidiTonebank = imidiCur;
                fFoundTonebank = TRUE;
            }
        }
    }

    // By the time we get here, we should have one of each
    if (!fFoundOutput || !fFoundTonebank) { MidiDone(); return 0; }

    // Open the MIDI device for playing the sequence
    if( midiStreamOpen(&hms, &imidiOutput, 1, (DWORD)hevent, (DWORD)NULL, CALLBACK_EVENT) != MMSYSERR_NOERROR ) { MidiDone(); return 0; }

    // Get the initial tempo for the port, so we can calculate the length of the
    // MIDI sequence (in case the sequence doesn't have a tempo change meta-event
    mpt.cbStruct = sizeof(mpt);
    if( midiStreamProperty(hms, (LPBYTE)&mpt, MIDIPROP_GET | MIDIPROP_TEMPO) != MMSYSERR_NOERROR ) { MidiDone(); return 0; }

    // Set the MIDI stream to receive SMF format rather than the Windows default MIDIEVENT format
    if( midiStreamProperty(hms, (LPBYTE)&fTemp, MIDIPROP_SET | MIDIPROP_SMF) != MMSYSERR_NOERROR ) { MidiDone(); return 0; }

    // Set the MIDI stream to map program changes to the General MIDI tonebanks
    if( midiStreamProperty(hms, (LPBYTE)&fTemp, MIDIPROP_SET | MIDIPROP_GENERALMIDI) != MMSYSERR_NOERROR ) { MidiDone(); return 0; }

    // Open a tonebank MIDI out port
    if( midiOutOpen(&hmo, imidiTonebank, (DWORD)NULL, (DWORD)NULL, 0) != MMSYSERR_NOERROR ) { MidiDone(); return 0; }

    // Open a tonebank MIDI out port for the drums
    imidiTonebankDrum = imidiTonebank + 1;
    if( midiOutOpen(&hmoDrum, imidiTonebankDrum, (DWORD)NULL, (DWORD)NULL, 0) != MMSYSERR_NOERROR ) { MidiDone(); return 0; }

    // Load the tonebank into memory
    if (!LoadTonebank(TEXT("test_tonebank"), &mhTonebank)) { MidiDone(); return 0; }

    // Load the tonebank into memory
    if (!LoadTonebank(TEXT("test_drums"), &mhTonebankDrum)) { MidiDone(); return 0; }


    // Convert to 32-byte aligned, so that it can be DMA'ed.  Note that in real life, this 
    // may not gain you anything.  That is, if you've already got a perfectly good pointer
    // to your tonebank data that you could use, you might waste more time aligning it,
    // preparing for DMA'ing, and then going through the thread blocking and switching so
    // that something else can run.  This is especially true for smaller blocks, but might
    // even be true for large ones.  Don't assume DMA will always win.  It is done here
    // simply to demonstrate one way to ensure that DMA is being used

    // Allocate a 32-byte aligned memory block and copy the tonebank to it
    pbTonebankNew = AllocAligned(mhTonebank.dwBufferLength, 32);
    if (pbTonebankNew == NULL) { MidiDone(); return 0; }

    memcpy(pbTonebankNew, mhTonebank.lpData, mhTonebank.dwBufferLength);
    mhTonebank.lpData = (char*)pbTonebankNew;

    // Allocate a 32-byte aligned memory block and copy the tonebank to it
    pbTonebankDrumNew = AllocAligned(mhTonebankDrum.dwBufferLength, 32);
    if (pbTonebankDrumNew == NULL) { MidiDone(); return 0; }

    memcpy(pbTonebankDrumNew, mhTonebankDrum.lpData, mhTonebankDrum.dwBufferLength);
    mhTonebankDrum.lpData = (char*)pbTonebankDrumNew;

    // Copy tonebank to sound RAM
    if( midiOutPrepareHeader(hmo, &mhTonebank, sizeof(mhTonebank)) != MMSYSERR_NOERROR ) { MidiDone(); return 0; }

    // Copy drum tonebank to sound RAM
    if( midiOutPrepareHeader(hmoDrum, &mhTonebankDrum, sizeof(mhTonebankDrum)) != MMSYSERR_NOERROR ) { MidiDone(); return 0; }

    // Now that the tonebanks are in the sound RAM, we no longer need the copies in system RAM
    FreeAligned(pbTonebankNew);
    FreeAligned(pbTonebankDrumNew);
    pbTonebankNew = pbTonebankDrumNew = NULL;

    // Set tonebank
    mhTonebank.dwFlags |= MHDR_GENERALMIDI;
    if( midiOutLongMsg(hmo, &mhTonebank, sizeof(mhTonebank)) != MMSYSERR_NOERROR ) { MidiDone(); return 0; }

    // Set drum tonebank
    mhTonebankDrum.dwFlags |= (MHDR_GENERALMIDI | MHDR_GMDRUM);
    if( midiOutLongMsg(hmoDrum, &mhTonebankDrum, sizeof(mhTonebankDrum)) != MMSYSERR_NOERROR ) { MidiDone(); return 0; }

    return 1;
}



void MidiDone()
{
    // Clean up
    if (hmo != NULL)
    {
        // Unprepare header; this frees up the audio RAM used by the tonebank
        if (mhTonebank.dwFlags & MHDR_PREPARED) midiOutUnprepareHeader(hmo, &mhTonebank, sizeof(mhTonebank));

        // If we allocated a new block of RAM for the tonebank, free it
        if (pbTonebankNew != NULL) FreeAligned(pbTonebankNew);

        // Close the MIDI out port.  This is very important; if all ports are not closed before 
        // the program exits, no other Dreamcast program will be able to use *any* audio
        midiOutClose(hmo);
    }

    if (hmoDrum != NULL)
    {
        // Unprepare header; this frees up the audio RAM used by the tonebank
        if (mhTonebankDrum.dwFlags & MHDR_PREPARED) midiOutUnprepareHeader(hmoDrum, &mhTonebankDrum, sizeof(mhTonebankDrum));

        // If we allocated a new block of RAM for the tonebank, free it
        if (pbTonebankDrumNew != NULL) FreeAligned(pbTonebankDrumNew);

        // Close the MIDI stream port.  See warning above about what happens if
        // all the ports that have been opened are not closed before program exit
        midiOutClose(hmoDrum);
    }

    if (hms != NULL)
    {
        // Unprepare header; this frees up the audio RAM used by the sequence
        if (mhOutput.dwFlags & MHDR_PREPARED) midiOutUnprepareHeader((HMIDIOUT)hms, &mhOutput, sizeof(mhOutput));

        // Close the MIDI stream port.  See warning above about what happens if all
        // the ports that have been opened are not closed before program exit
        midiStreamClose(hms);
    }

    // Free the event handle used to synchronize with MIDI playback
    CloseHandle(hevent);
}



int MidiPlay( const char* pszFilename, int looping )
{
    MMRESULT mmErr;
    TCHAR tszFilename[MAX_PATH], *tsz;
    g_looping = looping;
    strcpy( szCurrentMidi, pszFilename );

    tsz = tszFilename; while( *pszFilename ) *tsz++ = *pszFilename++;
    *tsz = 0;

   // Load the sequence into memory
    memset(&mhOutput, 0, sizeof(mhOutput));
    if (!LoadSequence(&mhOutput, tszFilename, &td, mpt.dwTempo)) return 0;
    
    // Reset the port to make sure stuff isn't left from the last sequence
    if( (mmErr = midiOutReset((HMIDIOUT)hms)) != MMSYSERR_NOERROR ) return 0;

    // Make sure the time division property of the MIDI stream is set
    mptd.cbStruct = sizeof(mptd);
    mptd.dwTimeDiv = td;
    if( (mmErr = midiStreamProperty(hms, (LPBYTE)&mptd, MIDIPROP_SET | MIDIPROP_TIMEDIV)) != MMSYSERR_NOERROR ) return 0;

    // Copy MIDI sequence to sound RAM
    if( (mmErr = midiOutPrepareHeader((HMIDIOUT)hms, &mhOutput, sizeof(mhOutput))) != MMSYSERR_NOERROR ) return 0;

    // Don't try this on the desktop!  It only works on Dreamcast because
    // after the header's been prepared, the sequence data has been copied
    // to the sound RAM and the system RAM copy is no longer needed.
    FreeSequence((BYTE*)mhOutput.lpData);

    // Get the MIDI sequence into the playback queue
    if( (mmErr = midiStreamOut(hms, &mhOutput, sizeof(mhOutput))) != MMSYSERR_NOERROR ) return 0;

    // Unpause the MIDI stream
    if( (mmErr = midiStreamRestart(hms) != MMSYSERR_NOERROR )) return 0;

    g_playing = 1;
    return 1;
}

void MidiUpdate()
{
    if( old_snd_MusicVolume != snd_MusicVolume )
    {
        WORD wVolume = snd_MusicVolume * 4369;
        old_snd_MusicVolume = snd_MusicVolume;
        midiOutSetVolume( (HMIDIOUT)hms, wVolume|(wVolume<<32) );
    }

    //if( mhOutput.dwFlags & MHDR_DONE )
    //if( g_playing && (WaitForSingleObject( hevent, 0 ) == WAIT_OBJECT_0) )
    if( mhOutput.dwFlags & MHDR_DONE )
    {
        g_playing = 0;
        //MidiStop();
        midiOutUnprepareHeader((HMIDIOUT)hms, &mhOutput, sizeof(mhOutput) );
        ResetEvent( hevent );
        if( g_looping )
        {
            MidiPlay( szCurrentMidi, g_looping );
            midiStreamRestart(hms);
        }
    }
}

void MidiStop()
{
    // Unprepare header; this frees up the audio RAM used by the sequence
    //midiStreamStop( (HMIDIOUT)hms );
    midiStreamPause( (HMIDIOUT)hms );
    midiOutUnprepareHeader((HMIDIOUT)hms, &mhOutput, sizeof(mhOutput) );
    g_playing = 0;
}



void MidiPause()
{
    midiStreamPause( (HMIDIOUT)hms );
}



void MidiResume()
{
    midiStreamRestart( (HMIDIOUT)hms );
}






//////////////////////////////////////////////////////////////////////////////////////////////////////////////



// DWORDs corresponding to the 4-character data tags for the chunks
#define MTHD  0x6468544D // Start of file
#define MTRK  0x6B72544D // Start of track

// Chunk header. dwTag is either MTrk or MThd.
typedef struct
{
    DWORD   dwTag;            // Type of chunk
    DWORD   dwChunkLength;    // Length of chunk (MSB first)
} MIDICHUNK;

// Contents of MThd chunk.
typedef struct
{
    WORD    wFormat;        // Format (MSB first)
    WORD    wTrackCount;    // Number of tracks (MSB first)
    WORD    wTimeDivision;  // Time division (MSB first)
} MIDIFILEHDR;

// Macros for swapping big/little-endian data
#define WORDSWAP(w)   (((w) >> 8) | (((w) << 8) & 0xFF00))
#define DWORDSWAP(dw) (((dw) >> 24)               | (((dw) >>  8) & 0x0000FF00) | \
                      (((dw) <<  8) & 0x00FF0000) | (((dw) << 24) & 0xFF000000))

// Some RIFF structures and constants
#define tagRIFF     0x46464952
#define tagRMID     0x44494d52
#define tagdata     0x61746164

typedef struct
{
    DWORD dwTag;
    DWORD dwChunkLength;
} typeRIFFChunk;

typedef DWORD RIFFFORM;

// This struct keeps track of current state information for the individual
// tracks found in the SMF Format 1 file while converting from Format 1 to Format 0
typedef struct tagTrack
{
    BYTE *pbTrack;
    DWORD cbTrack;
    BYTE *pbCur;
    DWORD tickEventNext;
    DWORD cbRunningStatus;
    BOOL fActive;
    BYTE bRunningStatus;
} typeTrack;


// This struct keeps track of the current state information for the final
// converted sequence, while converting from Format 1 to Format 0
typedef struct tagSequence
{
    DWORD dwTempo;
    DWORD tickLast;
    DWORD tickTotal;
    DWORD mtickTotal;
    WORD wTimeDiv;
    BYTE bRunningStatus;
} typeSequence;



/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    Converting SMF Format 1 to Format 0:

    The difference between Format 1 and Format 0 is that Format 0 has a single 
    MTrk chunk in the SMF file, while Format 1 may have more than one MTrk chunk.
    A Format 1 SMF file that has only one MTrk chunk is, for all intents and 
    purposes, a Format 0 file.

    Typically, a Format 1 file that has more than one track, there will be
    a track that is the tempo map, and contains only tempo changes, and then
    separate tracks for each individual instrument (ie, all of the commands will
    generally be for a single channel in each track).  One of the biggest
    advantages to doing it this way is data compression.  Because the channel
    for a given track is always the same, the status byte will be the same for
    subsequent commands more often, and thus running status can be used more
    often, reducing the data size.  As it happens, this is also one of the main
    pitfalls in converting Format 1 to Format 0; new status bytes may need to be
    written to the Format 0 sequence, when commands from one track follow
    commands from another track.

    The basic technique used here is as follows...

       * Read the SMF data into a buffer.  In this sample, the data is actually
         in a resource, and "reading" the data simply involves obtaining a pointer
         to the data in memory.

       * Parse the high-level file chunks, identifying each track in the file
         and saving a pointer to the start of each track in the file.

       * Finally, do a merge-sort on the individual MIDI commands in each track,
         writing the new commands, with new timestamps, inserting status bytes
         where necessary, to a single Format 0 track buffer.

    Additional details of the algorithm can be found in the code that actually
    implements the above technique.

-------------------------------------------------------------------*/


/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    MIDICommand

Description:

    Given the first byte of a MIDI command, return the length of the MIDI
    command, based on the command and whether the status byte for the command
    is actually present.

Arguments:

    int *pcbRunningStatus  --  Current count of bytes of running status command

    BYTE by                --  The first byte of the MIDI command

    BYTE *pbRunningStatus  --  Current running status byte

Return Value:

    The number of bytes actually present in the MIDI stream for the
    given command.  Also updates *pcbRunningStatus and *pbRunningStatus if
    the first byte is a status byte.

-------------------------------------------------------------------*/
int
MIDICommand(int *pcbRunningStatus, BYTE by, BYTE *pbRunningStatus)
{
    // Don't change running status for system realtime
    if (by >= 0xF8)
        return 1;

    // Check for system exclusive messages
    switch (by)
    {
    case 0xF0: case 0xF4: case 0xF5: case 0xF6: case 0xF7:
        *pcbRunningStatus = 1;
        *pbRunningStatus  = by;
        return *pcbRunningStatus;

    case 0xF1: case 0xF3:
        *pcbRunningStatus = 2;
        *pbRunningStatus  = by;
        return *pcbRunningStatus;

    case 0xF2:
        *pcbRunningStatus = 3;
        *pbRunningStatus  = by;
        return *pcbRunningStatus;
    }

    // Check for normal channel messages
    switch (by & 0xF0)
    {
    case 0x80: case 0x90: case 0xA0: case 0xB0: case 0xE0:
        *pcbRunningStatus = 3;
        *pbRunningStatus = by;
        return *pcbRunningStatus;

    case 0xC0: case 0xD0:
        *pcbRunningStatus = 2;
        *pbRunningStatus = by;
        return *pcbRunningStatus;
    }

    // If none of the above, count of bytes is same as the current running status
    // byte, excluding the status byte itself (since it's not actually present
    return (*pcbRunningStatus - 1);
}

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GetSMFInt

Description:

    Reads a variable length quantity from an SMF data block.

Arguments:

    BYTE **ppbMidi  --  Current pointer into the data block.

Return Value:

    The quantity read.  Also updates the current pointer into the data block 
    to point to the next byte after the variable length quantity.

-------------------------------------------------------------------*/
DWORD
GetSMFInt(BYTE **ppbMidi)
{
    DWORD dwRet = 0;
    BYTE bCur;

    // Variable length quantities are a series of bytes, each containing 7 bits
    // of the number, with the 8th bit set in all but the last byte of the number.
    // Number is stored MSB first in the data block.
    do
    {
        // Remember the current byte
        bCur = **ppbMidi;

        // Make room for the next 7 bits
        dwRet <<= 7;

        // Include the next 7 bits
        dwRet |= (bCur & 0x7f);

        // Go to the next byte
        (*ppbMidi)++;
    }
    while (bCur & 0x80);

    return dwRet;
}


/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    PeekSMFInt

Description:

    This is like GetSMFInt, except that it doesn't update the pointer.

Arguments:

    BYTE **ppbMidi  --  Current pointer into the data block.

Return Value:

    The quantity read.

-------------------------------------------------------------------*/
DWORD
PeekSMFInt(BYTE *pbMidi)
{
    return GetSMFInt(&pbMidi);
}

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WriteSMFInt

Description:

    This writes an variable-length integer to an SMF buffer, updating the
    destination pointer to the next byte after the just-written variable-length integer.

Arguments:

    DWORD dwDeltaTime  --  The integer to write

    BYTE  **ppb        --  pointer to the pointer to the buffer in which
                           to write the integer

Return Value:

    None

-------------------------------------------------------------------*/
void
WriteSMFInt(DWORD dwDeltaTime, BYTE **ppb)
{
    BYTE rgbT[4], *pbCur;
    BOOL fLastByte = TRUE;

    // Copy 7 bits at a time to our local buffer
    pbCur = rgbT;
    do
    {
        // Grab the lowest 7 bits
        *pbCur = (BYTE)(dwDeltaTime & 0x7f);

        // SMF stores numbers MSB-first.  This means the LSB -- the first 7 bits we see -- is
        // the last byte.  We need to set the high bit of every byte except the last one
        if (!fLastByte)
            *pbCur |= 0x80;
        else
            fLastByte = FALSE;

        // Shift the next 7 bits into position, and update our local buffer pointer
        dwDeltaTime >>= 7;
        pbCur++;
    } while (dwDeltaTime);

    // Copy the converted number to the actual destination, MSB first
    while (pbCur-- > rgbT)
        *(*ppb)++ = *pbCur;
}

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    AddEvent

Description:

    This routine parses the current SMF MIDI command.  It ignores the delta
    time for the event, because the delta time to be written is relative to the
    last event in the song, not necessarily the same as the last event in the
    current track.

    It also will not write the End-Of-Track meta-event if the fFilterEOT
    parameter is set.  This allows the caller to ensure that only the very
    last EOT event winds up in the final sequence data (having one in the
    middle is bad).

    Finally, in addition to copying the actual MIDI command data to the
    destination buffer, it tracks the accumulated time for the sequence.

Arguments:

    DWORD dtickNext          --  The actual delta time from the previous event

    BYTE **ppbSrc           --  Pointer to a pointer to the source buffer

    BYTE **ppbDst           --  Pointer to a pointer to the destination buffer

    BOOL fFilterEOT         --  TRUE if EOT meta-events should be ignored

    typeSequence *psequence --  Pointer to sequence state struct

    typeTrack *ptrack           --  Pointer to track state struct

Return Value:

    TRUE if the event was actually written, FALSE otherwise

-------------------------------------------------------------------*/
BOOL
AddEvent(DWORD dtickNext, BYTE **ppbSrc, BYTE **ppbDst, BOOL fFilterEOT, typeSequence *psequence, typeTrack *ptrack)
{ 
    int   cbCur;
    BYTE  *pbCur, *pbEOTSav;
    BOOL  fCopy = TRUE;
    BYTE  bEvent;
    DWORD dwTempoNew = 0;

    // Get delta-time (don't actually care what the time is, just need to 
    // read it to get our data pointer to the right place)
    GetSMFInt(ppbSrc);

    // Go ahead and write new delta to destination buffer
    // NOTE: we only write the last EOT event...save the current destination pointer in case we wind
    // up not writing the event, so that we can "back up" the destination pointer to the right spot
    pbEOTSav = *ppbDst;
    WriteSMFInt(dtickNext, ppbDst);
    psequence->mtickTotal += dtickNext;

    // Continue processing event
    pbCur = *ppbSrc;

    // Check the status byte
    switch (*pbCur)
    {
    case 0xf0:
    case 0xf7:
        // Sys-ex, or Sys-ex raw (handle both the same)
        // Skip status byte
        pbCur++;

        // Read the size of the sys-ex block 
        cbCur = GetSMFInt(&pbCur);

        // Dreamcast ARM7 driver doesn't handle sys-ex at all 
        psequence->mtickTotal -= dtickNext;
        *ppbDst = pbEOTSav;
        fCopy = FALSE;
        break;

    case 0xff:
        // Meta-event 
        // Skip meta-event status byte, get actual meta-event 
        pbCur++;
        bEvent = *pbCur++;

        // Get length of the meta-event 
        cbCur = GetSMFInt(&pbCur);

        // Actually need to do special things for the tempo change and EOT 
        switch (bEvent)
        {
        case 0x51: // tempo change
            // SMF spec says tempo changes are three bytes...this better be true 
            if (cbCur != 3)
                DebugBreak();

            // Get the value for the new tempo (24 bits, MSB first) 
            while (cbCur > 0)
            {
                cbCur--;
                dwTempoNew <<= 8;
                dwTempoNew |= *pbCur++;
            }

            // Accumulate milliseconds for sequence and reset MIDI tick counter 
            psequence->tickTotal += ((psequence->mtickTotal / psequence->wTimeDiv) * psequence->dwTempo) / 1000;
            psequence->mtickTotal = 0;

            // And of course, remember current tempo 
            psequence->dwTempo = dwTempoNew;
            break;

        case 0x2f: // end-of-track
        default:
            // Don't copy the EOT meta-event if we're filtering; and undo the timestamp that we already wrote 
            // Also, don't copy any other meta-events, since the ARM7 driver doesn't use them anyway 
            psequence->mtickTotal -= dtickNext;
            *ppbDst = pbEOTSav;
            if ((bEvent != 0x2f) || fFilterEOT)
                fCopy = FALSE;
            else
            {
                // EOT is the last event in the sequence.  No reason for it to
                // have any delay at all, and some sequences have really
                // screwed up values for this (ie, 20 minutes or so). 
                dtickNext = 0;
                WriteSMFInt(dtickNext, ppbDst);
            }
            break;
        }
        break;

    default:
        // Normal MIDI event 
        // Get the length of the current MIDI command 
        cbCur = MIDICommand((int*)&ptrack->cbRunningStatus, *pbCur, &ptrack->bRunningStatus);

        if (!(*pbCur & 0x80))
        {
            // If the current state of running status for the whole sequence
            // doesn't match the state for the track, we need to write the
            // status byte to the output sequence 
            if (ptrack->bRunningStatus != psequence->bRunningStatus)
            {
                *(*ppbDst)++ = ptrack->bRunningStatus;
                psequence->bRunningStatus = ptrack->bRunningStatus;
            }
        }
        else
        {
            // If we have a new status byte, but it matches the current status
            // byte, don't bother writing it.  (You wouldn't think that
            // this would happen normally, since any MIDI authoring tool
            // should already do this, but it turns out that there are plenty
            // of un-optimized sequences out there) 
            if (ptrack->bRunningStatus == psequence->bRunningStatus)
                *ppbSrc += 1;
            else
                psequence->bRunningStatus = ptrack->bRunningStatus;
        }
        break;
    }

    // Go to next MIDI command in SMF data 
    // NOTE: don't use cbCur directly, because it may not account for the complete data processed 
    pbCur += cbCur;
    cbCur = pbCur - *ppbSrc;

    // Copy the data, if it wasn't a filtered EOT meta-event 
    if (fCopy)
    {
        memcpy(*ppbDst, *ppbSrc, cbCur);
        *ppbDst += cbCur;
    }

    // Update the read pointer 
    *ppbSrc = pbCur;

	return fCopy;
}

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    MergeMidi

Description:

    Given a list of SMF tracks, a buffer into which to write a new single-track
    SMF sequence, and the relevant timing data for the sequence, this will do a
    merge-sort on the events in the SMF tracks.

Arguments:

    typeTrack rgtrack[]    --  List of tracks

    int ctrack         --  Number of tracks in list

    BYTE *pbMerged     --  Pointer to buffer to write new sequence

    DWORD *ptickTotal  --  Pointer to variable to take total milliseconds
                           for sequence

    WORD wTimeDiv      --  Time division for sequence, as given in the
                           original SMF file

    DWORD dwTempo      --  Initial tempo state for the sequencer
                           (practically all SMF sequences should have at
                           least one tempo change at the beginning, making
                           this information superfluous; however, it's nice
                           to have just in case)
Return Value:

    The length of the new MIDI sequence in bytes.  Also, copies the length, in milliseconds,
    to *ptickTotal.

-------------------------------------------------------------------*/
DWORD
MergeMidi(typeTrack rgtrack[], int ctrack, BYTE *pbMerged, DWORD *ptickTotal, WORD wTimeDiv, DWORD dwTempo)
{
    int          ctrackActive = ctrack;
    DWORD        tickTotal = 0;
    typeSequence sequence;
    BYTE         *pbMergedStart = pbMerged;
    DWORD        dtickNext = 0;

    // Initialize sequence state information 
    memset(&sequence, 0, sizeof(sequence));
    sequence.dwTempo = dwTempo;
    sequence.wTimeDiv = wTimeDiv;

    // Process MIDI events as long as we have 1 or more tracks with events in them 
    while (ctrackActive > 0)
    {
        DWORD tickMin = 0xffffffff, dtickCur = 0;
        int itrackCur;
        typeTrack *ptrack;
        BYTE *pbTrackMax;

        // Find the track with the earliest event 
        for (itrackCur = 0; itrackCur < ctrack; itrackCur++)
        {
            if (rgtrack[itrackCur].fActive && rgtrack[itrackCur].tickEventNext < tickMin)
            {
                ptrack = &rgtrack[itrackCur];
                tickMin = ptrack->tickEventNext;
            }
        }

        // Calculate the actual delta time for this event 
        // NOTE: we may not have written the previous event.  If that's the
        // case, we want to include the delta from that unwritten event 
        dtickNext += tickMin - sequence.tickLast;

        // Update our "last event" time state 
        sequence.tickLast = tickMin;

        // Very minor optimization 
        pbTrackMax = ptrack->pbTrack + ptrack->cbTrack;

        // Copy all the events at the current time to the main track 
        while (ptrack->fActive && dtickCur == 0)
        {
            // Only allow EOT event if this is the last active track 
            if (AddEvent(dtickNext, &ptrack->pbCur, &pbMerged, ctrackActive > 1, &sequence, ptrack))
            {
                // Any subsequent events happen at the same time.  NOTE: only reset this if we actually wrote the delta time 
                dtickNext = 0;
            }

            // If we still have data, read-ahead the next timestamp 
            if (ptrack->pbCur < pbTrackMax)
                dtickCur = PeekSMFInt(ptrack->pbCur);
            else
            {
                ptrack->fActive = FALSE;
                ctrackActive--;
            }
        }

        // Update current track time 
        ptrack->tickEventNext += dtickCur;
    }

    // Calculate total time 
    *ptickTotal = sequence.tickTotal + ((sequence.mtickTotal / sequence.wTimeDiv) * sequence.dwTempo) / 1000;

    // Return size of new sequence 
    return pbMerged - pbMergedStart;
}

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    AllocAligned

Description:

    This function allocates a block of memory, ensuring that the pointer
    returned is aligned on an aligned boundary.  This is useful for
    allocating memory which might need to be transferred via DMA, which
    requires all data transfers to be in multiples of 32 bytes, on 32-byte
    aligned boundaries.

Arguments:

    DWORD cb       --  Buffer size requested in bytes

    DWORD cbAlign  --  Byte boundary required

Return Value:

    A pointer to the allocated block of memory

-------------------------------------------------------------------*/

BYTE*
AllocAligned(DWORD cb, DWORD cbAlign)
{
    DWORD cbAlloc;
    BYTE *pbyAlloc, *pbyRet;

    // The actual block needs to be large enough to allow for saving the original pointer
    // of the block, as well as any extra space that might be needed to start the actual
    // space used by the caller on an aligned boundary
    cbAlloc = cb + sizeof(BYTE *) + cbAlign - 1;

    // Allocate the block 
    pbyAlloc = (BYTE *)LocalAlloc(LPTR, cbAlloc);
    if (pbyAlloc == NULL)
        return NULL;

    // Calculate a pointer that's between 0 and 31 bytes past an aligned address within the
    // block of memory, and also far enough ahead to allow us to save the original pointer
    pbyRet = pbyAlloc + sizeof(BYTE *) + cbAlign - 1;

    // Truncate that pointer back to the aligned address within the block of memory
    pbyRet = (BYTE *)((DWORD)pbyRet & ~(cbAlign - 1));

    // Save the original pointer in the memory just ahead of the pointer returned to the caller
    *(((BYTE **)pbyRet) - 1) = pbyAlloc;

    return pbyRet;
}

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    FreeAligned

Description:

    Frees a pointer that was allocated using AllocAligned

Arguments:

    BYTE *pbData  --  The block of memory to free

Return Value:

    None

-------------------------------------------------------------------*/
void
FreeAligned(BYTE *pbyData)
{
    BYTE *pbyAlloc;

    // Get the original address of the allocated block
    pbyAlloc = *(((BYTE **)pbyData) - 1);

    LocalFree(pbyAlloc);
}

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GetDataResource

Description:

    Given a resource name, return a pointer to the resource data.

    NOTE: we don't bother to remember the handle to the resource here.  This is
    because these resources will reside in the EXE, and are already loaded into
    memory with the EXE.  Freeing the resource would do no good as the data
    would still remain in memory, so don't we don't bother to worry about the
    handle, or freeing it later.

Arguments:

    TCHAR *psz      --  The name of the resource

    DWORD *pcbData  --  Pointer to a variable to take the length of the data

Return Value:

    A pointer to the data itself

-------------------------------------------------------------------*/
BYTE*
GetDataResource(TCHAR *psz, DWORD *pcbData)
{
    HRSRC   hrsrc;
    HGLOBAL hglobal;
    BYTE    *pbRet = NULL;

    // This series of statements is simply the standard Windows sequence for obtaining a 
    // pointer to a memory block that contains the data found in a resource included in the EXE
    hrsrc = FindResource(hInst, psz, RT_RCDATA);
    if (hrsrc == NULL)
        return NULL;

    *pcbData = SizeofResource(hInst, hrsrc);
    if (*pcbData == 0)
        return NULL;

    hglobal = LoadResource(hInst, hrsrc);
    if (hglobal == NULL)
        return NULL;

    return (BYTE*)LockResource(hglobal);
}

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GetDataFile

Description:

    Given a filename, opens and reads the data in the file into a single
    memory block.

Arguments:

    TCHAR *psz      --  The name of the file
    
    DWORD *pcbData  --  Pointer to variable to take file length in bytes

Return Value:

    A pointer to the data itself.

-------------------------------------------------------------------*/
BYTE *
GetDataFile(TCHAR *psz, DWORD *pcbData)
{
    HANDLE hFile = NULL;
    BOOL   fSuccess = FALSE;
    DWORD  cbFile, cbRead;
    BYTE   *pbRet = NULL;

    // Open the file
    hFile = CreateFile(psz, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        OutputDebugString(TEXT("Error: can't open data file \"%s\"\r\n"), psz);
        goto Fail;
    }

    // Find out how long it is, in bytes
    cbFile = GetFileSize(hFile, NULL);
    if (cbFile == 0xffffffff)
    {
        OutputDebugString(TEXT("Error: error getting file size\r\n"));
        goto Fail;
    }

    // Allocate a memory block to keep the file data
    pbRet = (BYTE*)LocalAlloc(LPTR, cbFile);
    if (pbRet == NULL)
    {
        OutputDebugString(TEXT("Error: failed to allocate %d bytes for file data\r\n"), cbFile);
    }

    // Read the data from the file
    ReadFile(hFile, pbRet, cbFile, &cbRead, NULL);
    if (cbRead != cbFile)
    {
        OutputDebugString(TEXT("Error: read %d bytes, expected %d bytes\r\n"), cbRead, cbFile);
    }

    // Store the file size and finish up
    *pcbData = cbRead;
    fSuccess = TRUE;

Fail:

    if (!fSuccess && pbRet != NULL)
    {
        LocalFree(pbRet);
        pbRet = NULL;
    }

    if (hFile != INVALID_HANDLE_VALUE)
        CloseHandle(hFile);
    return pbRet;
}



/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    LoadSequence

Description:

    Given a pointer to a memory block that contains an SMF format file,
    initializes a MIDIHDR structure with the first track found in the file,
    and also returns the time division.

Arguments:

    TCHAR   *pszFilename -- Name of the sequence to load
    
    MIDIHDR *pmh         --  The MIDIHDR structure to initialize

    WORD    *ptd         --  Variable to copy the time division into

Return Value:

    TRUE on success, FALSE otherwise

-------------------------------------------------------------------*/
BOOL
LoadSequence(MIDIHDR *pmh, TCHAR *pszFilename, WORD *ptd, DWORD dwTempo)
{
    BOOL        fRet = FALSE;
    MIDICHUNK   mthd;
    MIDICHUNK   mtrk;
    MIDIFILEHDR mfh;
    BYTE        *pbSequence, *pbSequenceCur;
    DWORD       cbSequence;
	DWORD       cbSequenceData;
	int         ctrack, itrack;
	DWORD       cbMidiTotal = 0;
	DWORD       tickTotal;
	BYTE        *pbMerged;
	typeTrack       *prgtrack = NULL;
	typeRIFFChunk   rchk;
	RIFFFORM    rfrm;

    // Get pointer to MIDI sequence
    pbSequence = GetDataFile(pszFilename, &cbSequence);
    if (pbSequence == NULL)
        return FALSE;

	pbSequenceCur = pbSequence;

    // May need to seek past some RIFF data
    if (*((DWORD *)pbSequenceCur) == tagRIFF)
    {
        if (cbSequence < sizeof(rchk))
            goto Fail;
        memcpy(&rchk, pbSequenceCur, sizeof(rchk));

        // Don't need to check tag...that's why where here
        pbSequenceCur += sizeof(rchk);
        cbSequence -= sizeof(rchk);

        // Data in the RIFF file ought to be MIDI data
        if (cbSequence < sizeof(rfrm))
            goto Fail;
        memcpy(&rfrm, pbSequenceCur, sizeof(rfrm));

        if (rfrm != tagRMID)
            goto Fail;
        pbSequenceCur += sizeof(rfrm);
        cbSequence -= sizeof(rfrm);

        // Now, check the actual data chunk that should contain the SMF data
        if (cbSequence < sizeof(rchk))
            goto Fail;
        memcpy(&rchk, pbSequenceCur, sizeof(rchk));

        if (rchk.dwTag != tagdata)
            goto Fail;
        pbSequenceCur += sizeof(rchk);
        cbSequence -= sizeof(rchk);

        // Should have enough bytes left in the file for what the chunk header says
        if (cbSequence < rchk.dwChunkLength)
            goto Fail;
    }

    // Read first chunk description; should be for the header
    if (cbSequence < sizeof(mthd))
        return FALSE;
    
    memcpy(&mthd, pbSequenceCur, sizeof(mthd));

    if (mthd.dwTag != MTHD)
        return FALSE;

    pbSequenceCur += sizeof(mthd);
    cbSequence    -= sizeof(mthd);

    // Read the rest of the header data.  NOTE: we must have at least sizeof(mfh)
    // bytes, but there may be more; only read what can fit into our data structure
    mthd.dwChunkLength = DWORDSWAP(mthd.dwChunkLength);
    if (mthd.dwChunkLength < sizeof(mfh))
            goto Fail;

    if (cbSequence < sizeof(mfh))
        goto Fail;

    memcpy(&mfh, pbSequenceCur, sizeof(mfh));
    pbSequenceCur += mthd.dwChunkLength;
    cbSequence    -= mthd.dwChunkLength;

    // SMF format specifies big-endian, but Dreamcast is little-endian
    mfh.wFormat       = WORDSWAP(mfh.wFormat);
    mfh.wTrackCount   = WORDSWAP(mfh.wTrackCount);
    mfh.wTimeDivision = WORDSWAP(mfh.wTimeDivision);

    // Only support Format 0 and Format 1
    if (mfh.wFormat > 1)
        goto Fail;

    ctrack = (mfh.wFormat == 0) ? 1 : mfh.wTrackCount;

    prgtrack = (typeTrack *)LocalAlloc(LPTR, sizeof(typeTrack) * ctrack);
    if (prgtrack == NULL)
        goto Fail;

    // Get pointers to all the tracks
    for (itrack = 0; itrack < ctrack; itrack++)
    {
        if (cbSequence < sizeof(mthd))
            goto Fail;
        memcpy(&mtrk, pbSequenceCur, sizeof(mthd));
        pbSequenceCur += sizeof(mthd);
        cbSequence  -= sizeof(mthd);

        // Verify track header
        if (mtrk.dwTag != MTRK)
            goto Fail;

        mtrk.dwChunkLength = DWORDSWAP(mtrk.dwChunkLength);
        if (cbSequence < mtrk.dwChunkLength)
            goto Fail;

        prgtrack[itrack].pbTrack = pbSequenceCur;
        prgtrack[itrack].cbTrack = mtrk.dwChunkLength;
        prgtrack[itrack].pbCur = pbSequenceCur;
        // Everyone starts at tick 0
        prgtrack[itrack].tickEventNext = PeekSMFInt(pbSequenceCur);
        prgtrack[itrack].fActive = TRUE;

        cbMidiTotal += mtrk.dwChunkLength;

        pbSequenceCur += prgtrack[itrack].cbTrack;
        cbSequence -= prgtrack[itrack].cbTrack;
    }

    // Worst-case scenario: a single status byte for a two-byte command,
    // followed by nothing but parameter bytes for the rest of the track,
    // in all of the tracks, with no track playing two commands
    // consecutively.  That is, we have a track that has no status bytes,
    // and we have to add a status byte for each command, doubling the
    // length of the sequence.  In reality, we should never see anything
    // that bad, but his will make sure we've got enough memory allocated
    // in any case

    // NOTE: for real run-time code, you could do the conversion twice...once
    // just to see how long the final output will be, and then again with a
    // block allocated to exactly the same size.  In real life, the new size
    // is usually very close to the original size, which means you're wasting
    // almost half the block of memory used for the sequence.

    // NOTE: of course, in real life, you should probably be converting
    // Format 1 to Format 0 when creating the content, and just loading
    // Format 0 data off the CD at run-time.

    cbMidiTotal *= 2;
    pbMerged = AllocAligned(cbMidiTotal, 32);
    if (pbMerged == NULL)
        goto Fail;

    cbSequenceData = MergeMidi(prgtrack, ctrack, pbMerged, &tickTotal, mfh.wTimeDivision, dwTempo);

    // If track chunk header checks out, set up MIDIHDR
    pmh->dwBufferLength = cbSequenceData;
    pmh->lpData = (char*)pbMerged;
    *ptd = mfh.wTimeDivision;
    fRet = TRUE;

Fail:

    if (prgtrack != NULL)
        LocalFree(prgtrack);
    if (pbSequence != NULL)
        LocalFree(pbSequence);

    return fRet;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    FreeSequence

Description:

    Helper function so that caller of LoadSequence doesn't need to actually
    know how the sequence data was allocated in memory
Arguments:

    BYTE *pbSequence -- The sequence to free

Return Value:

    None

-------------------------------------------------------------------*/
void
FreeSequence(BYTE *pbSequence)
{
    // Could also unload DLL data here if we'd loaded sequence that way
    FreeAligned(pbSequence);
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    LoadTonebank

Description:

    Loads the tonebank resource and initializes a MIDIHDR structure to point to
    the tonebank data.  Since the tonebank data is just raw data to be copied
    directly to the sound RAM, this is a lot simpler than loading a MIDI sequence.

Arguments:

    TCHAR   *tszName -- Name of the sequence to load
   
    MIDIHDR *pmh     -- The MIDIHDR structure to initialize

Return Value:

    TRUE on success, FALSE otherwise

-------------------------------------------------------------------*/
BOOL
LoadTonebank(TCHAR *tszName, MIDIHDR *pmh)
{
    BYTE *pbTonebank;
    DWORD cbTonebank;

    // Get the data
    pbTonebank = GetDataResource(tszName, &cbTonebank);
    if (pbTonebank == NULL)
        return FALSE;

    // Initialize the MIDIHDR
    pmh->lpData = (char*)pbTonebank;
    pmh->dwBufferLength = cbTonebank;

    return TRUE;
}

