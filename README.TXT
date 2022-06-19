WinDoom - V0.90

14 Jan, 1998

Thanks go first to id Software for making a great game
and then releasing the source code to it so we could
have something else to play with.

To anyone working on their own Win32 ports of Doom:
If you want to share programming information then all
you have to do is ask.  I'll tell you whatever I know
if it will help.  I AM going to release my modified
source code when I get this stabilized.


HIGH RESOLUTION MODES NOW AVAILABLE!

In order to know what video modes are available on
your system, look in the windoom.dbg file after you
have run the program at 320x200 resolution. Any
video mode that has an 8 in the third column is
usable unless the height is greater than the width.

The syntax for high resolution modes is:

-width xxxx -height yyy

where the xxxx is the width you want to use 
like 320 and the yyy is the height you want to
use like 240.

You can put these on your command line if you
create a shortcut to the program and modify
the command line in the attributes page of
the short cut's properties.


TAKE NOTE:

If you have read this document before you really should
re-read the whole thing again if the version number above
has changed. No telling what you might find changed...


DISCLAIMER

I make absolutely NO warrantees of any kind for this
program.  I am not responsible for any consequences
of anyone using this program.

id Software owns the rights to Doom and to the source
code they distributed.  This program was compiled from
source code to that game that was modified by me. So
don't bug id Software if you've got a problem with
this program.  I'm the one who screwed up. Tell me.


HELLO

This is my version (so far) of a Win32 port of the Linux
Doom source code released by id Software.  I have gotten
most of the features of the original program working but
it isn't quite ready for primetime.  It does odd things
occasionally, and sometimes sounds just disappear. Probably
because of the sound buffer manager being non-existent.

Please DO E-Mail me with problems you've had with this
especially if you can't get it working at all. I already know
of most of the problems you may encounter and I am already
addressing them.  But I want feedback about any problems
you encounter.  There is a file generated in your game
directory called windoom.dbg.  It contains some data that
will probably be helpful to me in debugging whatever problem
you've encountered. Screenshots may be helpful, too.

I have several very different systems to test this on and
a LAN as well but I couldn't possibly duplicate the variety
of systems you all have. Running it on your systems is
the best testing I can get.

I know this is more like a public Alpha test but I did want
to share what I have done so far, though.

Also, please don't send me E-Mails asking for features or
changes.  There will be time enough for that after the
game actually works properly.

New revisions will be forthcoming soon.

Also, when I've got all the original Doom features working
and the program stabilized, I will release my source code
for the game.

Also, after I get all the enhancements added to the game
that I want to add, I will release the source code to
that as well.  I've detailed a couple of them below. This
probably won't be before the summer, though. I've got a
LOT planned.

Also, if you're a Doom purist.  Why are you reading this?


REQUIREMENTS

This program is a Win32 application and REQUIRES DirectX 5
(sorry NT folks).  It would have been possible to do what
was done with DirectX 3 but I've already installed DirectX
5 and wanted to use it.  DirectX 5 will be supported in the
5.0 version of NT. (Yes, I KNOW Microsoft says you can write
DirectX 3 compatible software using DirectX 5.  I didn't want
to.)  If you don't have DirectX 5, you can get it here:

http://www.microsoft.com/msdownload/directx5/directx5.htm

If you want to run ANYTHING under Windows95 you really should
have at least 16 Meg of RAM.  32 Meg is MUCH better.

WHAT'S WORKING?

Video - DirectDraw is being used as a flipping surface with
        two surfaces.  The game is rendered into a memory
        area then copied to the back DD buffer.  The palette
        is updated through the DirectDraw surface attached
        palette. All video works.  An initial attempt was
        made to increase the resolution but was not entirely
        successful.  Default screen resolution is 320x200.

Sound - DirectSound is being used for playing the sounds.
        Currently, the sounds play until they are finished
        and do not loop as in the original game.  Nor can
        they currently be stopped. This is being worked on
        and will be functional in a few days.  Volume control
        and panning are both working adequately.  Buffer
        management is non-existent at this point.  It is
        being worked on and a proper sound buffer manager
        will be forthcoming.  The volume controls on the
        menu DO NOT WORK YET. I haven't even looked at them.


Network - The network code is there and works. The syntax
        for a network game is a little odd but it works.
        Please see "How do I play a network game?" for details.
        I used the Linux code that was already there and
        adapted it to WinSock2.


Music - I haven't had the time to get a MUS to MIDI con-
        version written, yet. But I do have code to play a
        midi file "doomsong.mid".  There is also a little
        surprise as you read on.


Input - DirectInput and the Windows message loop are used to
        handle keyboard, mouse and joystick input.  Not all
        the keys on the keyboard have been mapped.  Notably
        missing, so far are most of the keys in the numeric
        keypad and some of the navigation keys.  Pause DOES
        work.  The page-up and down keys as well as home,
        end, insert and delete are not normally used anyway.
        There is also a "console" key which is "`".

Demos - The demos now work.  Beware trying to play a demo for
        which you do not have the correct IWAD or PWAD file
        loaded for.  It can cause weird things to happen
        in the game and even crash the machine.  The demos
        now appear to be 100%.


HOW DO I USE IT?

Create a directory and put the WinDoom.exe program in it
along with the Doom IWAD of your choice  (I've tested this
with all three of the Doom I wads (doom1.wad, doom.wad and
doomu.wad) as well as doom2.wad, tnt.wad and plutonia.wad.

The order of precedence in looking for an IWAD is this:

doom2.wad - retail Doom II wad file
doomu.wad - ultimate Doom I retail wad file
doom.wad  - Doom I registered shareware wad
doom1.wad - Doom I unregistered shareware wad
tnt.wad   - Another Doom II IWAD from id
plutonia.wad - Another Doom II IWAD from id

If you have "Ultimate Doom" you need to rename your IWAD
to doomu.wad.  (it's dumb I know) If you don't, the program
will think that you have the original Doom I loaded and
will try to cycle to a screen that isn't there and die.
(I'll fix that when I get time.)

When the program is first run, it will create a section in
the win.ini file for WINDOOM that stores the location of
the WinDoom program.  If you move the program or change the
name of the directory in which the program is installed you
need to update this ini file entry or remove it.

An ini file will be created (or updated) in the directory
in which WinDoom is run with the configuration information
for the program. All numeric entries are either boolean
(0 = false, 1 = true), keyboard scancodes or ASCII character
values. Modifying this file is currently the only way to
change some of the keyboard/mouse/joystick mappings.  A way
to modify this in the game or a setup program will be
forthcoming.  I am going to make it possible to set these
values from within the program from the console.  When this
is finished there will be a published list of cvars that you
can set to setup your controls. (i.e. always_run )

A general rule to go by if you want to edit the windoom.ini
is that printable characters use the ASCII value.  Non-printable
keys (ESCAPE, RETURN, ARROWs, etc.) use keyboard scan codes.
It's confusing, but that's the way it works.

Make sure your shortcut, if you create one, has the directory
where you installed the program as the working directory.  It
probably won't run otherwise.

I have not tried some of the original command line options to see
if they work or not.  I have spent most of my time writing code
to get the program working.  I will be testing the rest of these soon.

I have tested the following and know that they work:

-nomonsters
-deathmatch
-net
-skill
-warp
-episode
-playdemo
-timedemo

The others will probably work but I have not tested them.


HOW DO I PLAY A NETWORK GAME?

Okay, this is little different than a DOS Doom network game.
It's just like the Linux parameters, though.

What you want to do is create a shortcut to your game and
then change the parameters of your shortcut to include the
network commands on the command line.

The parameter to start a network game is "-net" (without the
quotes).  You then follow the -net command with the player
number your machine is going to be (1 to 4) and the IP
addresses or hostnames of the OTHER systems you will be
playing with. The IP addresses MUST be preceded by a period
".". If you leave off the leading period, the game will
think that the IP address is a hostname and try to resolve
it into an IP address (and die on you).

Sample command lines for two players would look like this:

machine 1: (hostname: rimmer IP address: 192.168.1.5)
windoom -net 1 holly -deathmatch -nomonsters
OR
windoom -net 1 .192.168.1.4 -deathmatch -nomonsters

machine 2: (hostname: holly IP address: 192.168.1.4)
windoom -net 2 rimmer -deathmatch -nomonsters
OR
windoom -net 2 .192.168.1.5 -deathmatch -nomonsters

In order to use hostnames rather than IP addresses you
must either have DNS setup or have a valid hosts file.

If you add a third or fourth machine to the game you need
to add the IP addresses of the OTHER machines to the
command line on each machine. You do not put your own
machine's IP address on the command line.  You also
do not put how many machines are in the game after the
-net command.  Only which player, out of the 4, you are.

The player numbers must be contiguous.  You can't have
players 1,2 and 4.  Also, one player MUST be player 1.
Player 1 is the KEY player and that machine coordinates
all the other systems.

The number of players in the game is determined by how
many IP addresses you put on the command line plus your
machine.

The command line on the KEY player's machine in a four
player game might look like this:

windoom -net 1 .192.168.1.3 .192.168.1.4 .192.168.1.5 -deathmatch -nomonsters
OR
windoom -net 1 cat holly rimmer -deathmatch -nomonsters

The other player's command lines in the same game might
look like this:

windoom -net 2 lister holly rimmer -deathmatch -nomonsters
OR
windoom -net 2 .192.168.1.2 .192.168.1.4 .192.168.1.5 -deathmatch -nomonsters

windoom -net 3 lister cat rimmer -deathmatch -nomonsters
OR
windoom -net 3 .192.168.1.2 .192.168.1.3 .192.168.1.5 -deathmatch -nomonsters

windoom -net 4 lister cat holly -deathmatch -nomonsters
OR
windoom -net 4 .192.168.1.2 .192.168.1.3 .192.168.1.4 -deathmatch -nomonsters

If you start a network game and the program appears to be
"hung" (black screen only), press and hold the escape
key for a few seconds.  The program will terminate. It
generates an error when shutting down but it doesn't
affect game play.  I should have that error figured out
soon.

I DO NOT know if the UDP datagrams used are robust enough
to allow this to be played over the internet.  My assumption
is that it would be but I don't know. I haven't tried it.

I have started up a four player game on my network and
played at all four stations. Response was good and play
appeared to be smooth.

I'd be interested to know if anyone is able to play this
over the Internet with all the problems that entails. I can't
because of my router.


BEFORE SOME OF YOU ASK

If you only have the Doom shareware IWAD, you CANNOT use
the Plasma gun or the BFG9000. They just aren't in the
WAD file to use.  You also can't use the double-barreled
shotgun in Doom I.  There are no sprites for those things
in those wads.  It's not something you can change in the
program.


BUG FIXES:

There appear to be some video cards that have multiple
display sync rates at various resolutions.  It may be
necessary to have a setup program that will let you
pick the sync rate you want to use at any given
resolution in order for some monitors to be able to sync
to them.  I am working on this at this right now.

Added normal VGA mode (320x200x8) support to DirectDraw
instead of just ModeX.  This may fix the few remaining
video problems. (I hope...) (no, it didn't :(

Notice to 3Dfx card owners.  Sorry I didn't test this on the
3Dfx machines earlier. I have one but didn't think it would
interfere with the game running.  (Boy, was I wrong...) It
works now. (I don't have one on my development systems...)
Oddly enough, the Obsidian card doesn't do what the Monster
3D does.

There was a bug in the sound volume code that wasn't using
the full volume range.  It now does.

Changed mouse mode to non-exclusive because switching from
the game to something else completely locked up the mouse.

I have gotten some reports of problems from people who have
S3 Trio/64 video cards that their video is "screwy". The
display appears to be in the top half of the screen only.

I have modified the blitting code to the back surface to
try to alleviate this.  I would like to know if this was
successful.  I don't have a Trio/64 card to test it on.

The DirectDraw problem of not enough memory to create
surface should be fixed.  I have been able to reproduce
the failure and changed to the code to work around it.

The IDCLEV cheat code did not work in DoomII or Final-
Doom. This has been fixed in the game and the console.

Palette index problem with indices 0 and 255 is fixed.

WHAT'S NEW?

A few new things have been added along the way.

1. A print screen key is now always available by pressing
   the (Print Screen/Sys Rq) key on your keyboard.  If you
   aren't playing a game, no message will appear on the
   screen but a print screen PCX file WILL be generated.

2. I have added a console similar to the Quake/Quake II
   console.  It isn't as fancy and no doubt not as functional
   as the Quake console but it works and any keyboard command
   such as the cheats can be entered in the console.  Also,
   all messages that appear on the screen briefly will be
   displayed in the console.  The console key is the "`"
   key.  The following commands are currently implemented:

   iddqd         - god mode
   idfa          - full ammo
   idkfa         - keys full ammo
   idclev        - change level
   idchoppers    - chainsaw and invulnerability
   idclip        - no clipping toggle
   idspispopd    - no clipping toggle
   idbeholdi     - invisibility
   idbeholdv     - invulnerability
   idbeholds     - strength (berserk pack)
   idbeholdr     - radiation/environment suit
   idbeholdl     - light amplification goggles
   idbeholda     - all map cheat
   cd on         - starts your cd player (switches from midi)
   cd off        - stops your cd player (switches to midi)
   cd pause      - pause/resume cd music toggle
   cd resume     - pause/resume cd music toggle
   cd next       - play next song on cd
   cd +          - play next song on cd
   cd prev       - play previous song on cd
   cd -          - play previous song on cd
   cd XX         - plays song number specified in XX 00 to 99
   midi pause    - pauses/resumes the midi playback (toggle)
   midi resume   - pauses/resumes the midi playback (toggle)
   quit          - quits the game (immediately)
   god           - enable god mode (degreelessness?) toggle
   map           - e?m? or map?? (Doom I or Doom II map names)
   noclip        - no clipping toggle
   give all      - gives full ammo,armor,health,weapons,keys
   give ammo     - gives full ammo
   give armor    - gives full armor
   give health   - give 100% health
   give weapons  - gives all weapons
   give keys     - gives all keys
   give backpack - gives ammo backpack
   always_run X  - toggles always run 0 = off, 1 = on

   The map and idclev commands are disabled from the console
   during a network game. It crashes the machine you do it
   on and locks up the KEY player's machine.  The other players
   can exit the game but their systems are VERY slow. (You
   have to hold the keys longer.)

   All the original cheat codes work EXACTLY as they did
   originally.  No changes have been made to those. The
   new MAP command works similarly to the MAP command in
   Quake/QuakeII. If you want to select a Doom 1 or Doom
   II level you type in MAP then the full name of the
   map you want to load (E1M7 or MAP19).

   All the cheats are disabled during network games, also.
   Note: This does not include the game control commands,
   just the "cheats".

   A number of other commands are planned for this. Mostly
   just game variables that you can set. (like always_run)

   All game input is dead while the console is active, so
   be warned! The <ESCAPE> key as well as the "`" key will
   terminate the console.  Any command that you have not
   pressed <ENTER> to complete will be thrown away.  The
   menu and console shut each other down when you call
   them up.  They are mutually exclusive.

   The console was done because I wanted to support the CD
   player and there simply weren't enough keys available to
   assign keys to handle this and keep the original cheat
   codes.  Also no menus can be added without hacking the
   original menus to bits and reassembling them.  That was
   too much trouble.  Besides the console is very flexible.
   All sorts of new commands can now be implemented.

3. As you see above, a CD player is now supported.  A number
   of features are planned for this (playlists, directory,
   naming, song naming, etc.)  Trying to play a CD with no
   CD in the drive will do nothing.  Removing the CD from the
   drive while playing will result in the MIDI song being
   restarted.  The CD player will detect if the CD has been
   changed and start playing on the first music track (if
   there is one) and will not play if there are no music
   tracks.

4. Midi file playing. Currently a single MIDI file will be played
   (if it exists) in the game directory. The name of this file is
   doomsong.mid.  It can be any valid MIDI file.  It will be played
   ALL the time unless you turn on the CD player.

5. There is now an "always_run" key. I got this idea from Chi
   Hoang and his DOSDoom. The always_run key is the <CAPS LOCK>
   key and it toggles between on and off. This key state is
   saved in the windoom.ini file.


WARNINGS!


Context switching (switching to other programs) while playing this
program MAY LOCK YOUR MACHINE UP.  (This is being looked into.)
The fix is probably very simple.  I haven't looked very hard.

This program is by no means ready for prime time but it does work
mostly.  The original music was a large part of Doom for some of
us and this game isn't complete without it. It IS being worked on.
It may not be possible, however, to play against other versions of
Doom with this code.  I DO have the specifications for the IPX
protocol used by the original Doom and I will attempt to make that
work as well.

Supporting DOS Doom in network games is, therefore, doubtful but
it may happen.  However if Chi and I can maintain the same message
data for the networking, you should be able to play network games
between the two.

WHAT'S COMING?

Note the version is on the console on the bottom right.  Something
I "stole" from Quake's console.  It's a good idea with a Win32
game to have SOME way to see what version you are running.

The volume control for music will control which ever music mode
is currently selected when it's done.  It isn't done yet.

I am going to add my OpenGL Doom level viewer as the video output
portion of Doom.  I already have ALL the code to generate the levels
as polygons, OpenGL texture creation and rendering of the level.

I have enclosed a screen shot of the OpenGL Level Viewer so you can
get an idea of what that Doom will look like with an OpenGL renderer.

This will mean replacing most of the current renderer or at least
making major modifications to it so that will be fairly slow in
coming.

Once the game has been converted to a polygon renderer (not as
simple as it sounds), I am going to add the ability to look
(and aim) up and down.  I am also going to add a crosshair.

Before I get ahead of myself, let me say that I have a zillion
other changes in mind but the program needs to get back to the
level of the commercial release before any other modifications
are made.

The CD player was added as a replacement for the missing Midi music.
I know it's not the same but you can pick whatever music you want
while you're playing Doom, now. I like cut 6 on the Quake II CD!

The console was necessary to make the CD interface possible. It
was ridiculously easy to do.  I guess id just hadn't thought of
it when Doom was released or maybe it didn't fit with their
design.  Who knows. You don't have to use if you don't want to.
It's ALWAYS available, too.

There will probably be a Win32 dialog box interface created as
the front-end of the program similar to the Doom95 dialog box.

Most of the features (if not all) of that dialog will be duplicated
since most of them are necessary.  This will be available before
the move to OpenGL or any other modifications.  It's a pity we
didn't get that source code so we wouldn't have to recreate
so much of it.  Oh, well, we learn more this way...


THAT'S ALL FOLKS

Notice the DOOM98 in the top right corner of the screen? Please
don't copy that if you are working on your own Win32 port. Or,
at least make yours look different.  (The console I mean.)  The
look of mine is set and I am not going to change it.

Enjoy it if you can...

Bruce Lewis 
brucel@abraxis.com


Thanks to all of you who have downloaded the program (I'm not
calling it a game. The game part comes from id!).  Your feedback
has been very helpful and has made this a better program.

And to those of you who have had problems.  I thank you for
your patience while I worked out the bugs you've reported.

Thanks again to id Software for making Doom.

Microsoft(tm)(c) 1975-1998, Microsoft, Inc., All Rights Reserved.
Quake(R)(c) 1996, id Software, Inc. All Rights Reserved.
Quake II(R)(c)1997, id Software, Inc. All Rights Reserved.
DOOM(R)(c) 1993, id Software, Inc. All Rights Reserved.
DOOM(R) and the DOOM image are registered trademarks of
id Software, Inc.

