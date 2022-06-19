

#ifndef I_MIDI_H
#define I_MIDI_I

int MidiInit();
void MidiDone();

int MidiPlay( const char* pszFiename, int looping );
void MidiStop();

void MidiUpdate();

void MidiPause();
void MidiResume();


#endif
