//////////////////////////////////////////
//                                      //
// SIMPLEST WINDOWS PROGRAM             //
//                                      //
// You found this at bobobobo's weblog, //
// http://bobobobo.wordpress.com        //
//                                      //
// Creation date:  Jan 31/08            //
// Last modified:  Feb 9/08             //
//                                      //
//////////////////////////////////////////

#ifdef _MSC_VER
#    pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include <windows.h>
#include <stdio.h>
#include "MMShellHook.h"

// Function prototypes.
LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow );

////////////////////////////
// Introduction:
// Basic Windows Program!
//
// This package demonstrates how to build a very basic Windows application
// on a Win O/S system from Windows 3.1 to Windows XP using C++ code.
//
// * Prerequisites to understanding this program:
//     - Already understand how to create Console applications in C++.
//     - Full understanding of C FUNCTIONS, FUNCTION PARAMETERS/ARGUMENTS.
//
// If you don't know what those are, go learn what
// they are before going on reading this!
// 

///////////////////
// OVERVIEW:
// Windows applications in C++ are easy!
// To understand them, you must first see the big
// picture.  Then you can get your hands dirty 
// and get right into the code.

///////////////////
// Big picture.
//
// Windows apps are much different than console apps.
// A console app, (which you probably are used to)
// has just a single "main" function called main().

// Every Windows app has __2__ functions that are very
// important to it.

// These 2 functions are WinMain and WndProc.  WinMain
// and WndProc really form the Windows' app's heart and soul.
// 
//    A.  WinMain:  Application STARTING POINT.  REPLACES
//                  main() function that you might be used to
//                  from regular C/C++ programs.
// 
//    B.  WndProc:  A function that PROCESSES MESSAGES from
//                  the Windows O/S as they come in.
//

///////////////////
// BUT what's a MESSAGE???
//
// The idea of "messages" takes some getting used
// to, but it is really a simple concept.
//
// The Windows Operating system is like a GOVERNMENT.
//
// All of the little windows that live inside
// (the Firefox window, the MSWord window,
// and YOUR PROGRAM's window!) are people owned
// by the Windows GOVERNMENT.
// 
// So, whenever the user attempts to interact
// with ANY program window inside that Windows Government,
// either by clicking on your window, or by pressing a key
// while your program has the "input focus" (when
// your window is "selected"),
// the Windows O/S INTERCEPTS that communication FIRST.
//
// THEN, a fraction of a second later, (almost
// instantly), the Windows O/S SENDS A a "MESSAGE"
// to YOUR Window program that "HEY! THE USER
// CLICKED ON YOU AT LOCATION (22, 405), USING
// THE RIGHT MOUSE BUTTON."  or "HEY!  THE
// USER PRESSED THE 'A' KEY, AND HE WAS ALSO HOLDING
// DOWN SHIFT WHILE HE PRESSED IT."

// THAT is what a MESSAGE is.  Its a notification
// from the Windows O/S that the user has 
// done something to your program's window.

// ONCE your program receives this
// "MESSAGE", your program can THEN execute some code
// in response to that particular MESSAGE.

// The WndProc function will contain ALL of
// your "MESSAGE HANDLING CODE" -- that is,
// the code pieces that you want executed 
// when certain window events happen.

// This is called EVENT DRIVEN PROGRAMMING.
// And in most standard Windows applications, this is
// how things happen.

// Most of a basic, standard Windows application's
// time is spent WAITING for events.

// And that is what a message is!

//////////////////////////////
// OF INSTANCES AND HANDLES.
//
// There are 2 concepts you must understand intuitively first
// before diving into Windows programming.

// Those concepts are the concept of an INSTANCE,
// and the concept of a HANDLE.

///////////////
// INSTANCES:
// The first concept is the concept of an INSTANCE of a program.

// What's an INSTANCE?

// An INSTANCE of an application is just one running OCCURRENCE of it.
// If you open up 3 different NOTEPAD.exe windows, then you have
// created __3__ different, separate INSTANCE of the NOTEPAD program
// inside your Windows Kernel.

// If you're familiar with OOP, an easy explanation is this:
    // PROGRAM CODE >> like a C++ class definition.
    // ACTUALLY RUNNING PROGRAM CODE >> like an "instance" of the class, this is an INSTANCE of the program.


///////////////
// HANDLES:
// HANDLES pop up EVERYWHERE in Windows programming (and all other
// types of programming as well!)  So I'm hoping to explain the idea
// behind a HANDLE intuitively, so that you have something to "hold onto"
// whenever you see use of HANDLES in program code.

// Think about a POT of boiling water.  Inside that pot is
// some corn on the cob being cooked.

// Now, say you want to ACCESS the pot, so you can dump its
// contents out into the sink and drain the corn.

// How do you do that?  Do you GRAB THE POT DIRECTLY??? NO!!
// That would be stupid.  Instead, you grab the HANDLE TO THE POT.
// Using the HANDLE to the pot, you manipulate the pot, slowly
// dumping out the water and leaving the corn behind.  Then you
// eat the corn and it is delicious.

// Now, in programming, the idea of a HANDLE is much the same.
// A HANDLE to a WINDOW is __NOT__ the window itself in an application
// variable.  Instead, it is a POINTER TO, A REFERENCE TO the
// window itself.

// A HANDLE TO AN INSTANCE in an application variable is NOT
// the application INSTANCE itself.  Rather, it is a POINTER TO
// that application instance.  The application instance exists
// somewhere in the Windows O/S's program memory.  You use the
// programmatic HANDLE that you have as YOUR MEANS TO MANIPULATE
// AND DEAL WITH that application instance.

// The benefits of HANDLES are many!  You'll see as we go on.
// Onto WinMain()!

////////////////////////////
// In a C++ Windows app, the starting point is WinMain().
int WINAPI WinMain( HINSTANCE hInstance,    // HANDLE TO AN INSTANCE.  This is the "handle" to YOUR PROGRAM ITSELF.  More in the GLOSSARY at the bottom.
                    HINSTANCE hPrevInstance,// USELESS on modern windows (totally ignore hPrevInstance)
                    LPSTR szCmdLine,        // Command line arguments.  Explained near BOTTOM of this file.
                    int iCmdShow )          // Start window maximized, minimized, etc.
{
    // As we said before, WinMain is the application starting point.
    
    // A:  WinMain does 2 main things:
    //    1.  STARTUP STUFF:  CREATE THE WINDOW ITSELF, AND LOAD IT UP
    //        SO IT APPEARS ON THE SCREEN.
    //
    //    2.  KEEP CHECKING WITH WINDOWS O/S TO SEE IF THE USER
    //        HAS INTERACTED WITH THE APPLICATION ("MESSAGE LOOP")
    //        If the user has clicked on anything, or pressed any keys while
    //        our window is ACTIVE (our window has the "input focus")
    //        then we are to DISPATCH a MESSAGE to WndProc (make
    //        a function call to WndProc) that tells
    //        WndProc EXACTLY what the user did to our window (clicked?
    //        key pressed?), when it happened, etc.  WndProc then
    //        has the opportunity to EXECUTE SOME CODE in response
    //        to that particular user interaction.
    
    #pragma region part 1 - STARTUP STUFF
    // A.  Create WNDCLASS structure and initialize it
    // The WNDCLASS structure tells Windows WHAT KIND OF
    // WINDOW we dream of creating.
    
    // A note:  Use the TEXT() macro whenever you have a
    // string value that gets passed to a Windows
    // function.  Its good and makes life easier.
    WNDCLASS wc;
    wc.cbClsExtra = 0;  // ignore for now
    wc.cbWndExtra = 0;  // ignore for now
    wc.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH );   // I want the window to have a white background
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );            // I want it to have an arrow for a cursor
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );        // I want it to have that envelope like icon
    wc.hInstance = hInstance;           // INSTANCE HANDLE -- see the GLOSSARY PART of this file for an explanation of what HINSTANCE is
    wc.lpfnWndProc = WndProc;           // Give name of WndProc function here.
    wc.lpszClassName = TEXT("Philip");  // I have named it Philip.
                                        // You could name it anything
                                        // you want, but you have to
                                        // remember the name for when
                                        // you call CreateWindow().
    wc.lpszMenuName = 0;    // no menu - ignore
    wc.style = CS_HREDRAW | CS_VREDRAW; // Redraw the window
    // on BOTH horizontal resizes (CS_HREDRAW) and
    // vertical resizes (CS_VREDRAW).  There are
    // many more window class styles!

    
    // B.  Register the WNDCLASS with Windows, THEN
    //     create the window.
    RegisterClass( &wc );   // This kind of "plants" the information
                            // about the Window we "dream"
                            // of creating somewhere inside the Windows O/S...
    
    // NOW, at this next stage, WE ACTUALLY CREATE
    // the window.  The previous lines of code
    // until this point have only been PREPARATION.

    // When we call the CreateWindow() function, we will
    // make a reference to this WNDCLASS structure (BY ITS
    // NAME -- "Philip"), and the Windows government
    // will grant us our wish and a REAL LIVE WINDOW,
    // with the properties that we specified in the
    // WNDCLASS structure!

    // NOTICE that the value that is returned from
    // CreateWindow is a variable of type HWND.

    // HWND is a "handle to a window" - its a programmatic
    // reference variable to the Window.
    // The HWND is OUR MEANS BY WHICH to manipulate
    // our Window.

    // Read the schpeal near the top of this file if
    // not sure about HANDLES.

    // Most of the time, you would want to save
    // this HWND into a global variable,
    // so you wouldn't lose it later.
    HWND hwnd = CreateWindow(
        TEXT("Philip"),         // THIS IS THE LINK
                                // to the WNDCLASS structure that
                                // we created earlier.

        TEXT("window's title!"),// appears in title of window

        WS_OVERLAPPEDWINDOW,    // STYLE of window.  WS_OVERLAPPEDWINDOW just means
                                // the window we create should have a few common features
                                // like a minimize box, a maximize box, and it should
                                // be resizeable by dragging the "thick frame" around
                                // the window. There are other styles
                                // and they all start with WS_.  Check it out in the
                                // autocomplete by typing WS_ THEN PRESSING CTRL+SPACE
                                // to make the autocomplete window come up.
        10, 10,                 // x, y start coordinates of window
        200, 200,               // width, height of window
        NULL, NULL,             // nothing and nothing (ignore to start out)
        hInstance, NULL );      // hInstance -- (see glossary), nothing

    // Next, SHOW and PAINT the window!
    // You won't see the window if you DO NOT
    // call ShowWindow();
    ShowWindow(hwnd, iCmdShow );
    UpdateWindow(hwnd);

    printf("loading...\n");
    LoadLibraryA("MMShellHook.dll");
    int statshook = SetMMShellHook(hwnd);
    printf("WHAT %d\n", statshook);

    setvbuf(stdout, NULL, _IONBF, 0);
    printf("{\"action\":\"connected\"}\n");

    #pragma endregion

    #pragma region part 2 - ENTER A LOOP TO CONTINUALLY KEEP CHECKING WITH WIN O/S FOR USER INTERACTION
    // first, we create the MSG structure.
    MSG msg;
    // But WTF IS A MESSAGE???
    // A MESSAGE is something that the Windows O/S
    // SENDS your application program when
    // SOMETHING HAPPENS TO YOUR WINDOW.

    // Messages can be anything from "the user
    // has moved your window", to "the user
    // has clicked at pixel location (20, 20)" or,
    // "you need to paint yourself", or, 
    // "you have been maximized".

    // YOUR CHANCE to handle those "messages"
    // that get passed to your window comes
    // IN WNDPROC.
    while( GetMessage( &msg, NULL, 0, 0 ) )
    {
        // GetMessage is a function that will not
        // return until the Windows O/S HAS A message
        // for our program.

        // Since the GetMessage() function call is
        // INSIDE the bracket for the while Loop,
        // this means that our program is essentially
        // "put on hold" or halted until the GetMessage function
        // returns.

        // If and when the user interacts with our
        // application's window, then the GetMessage()
        // function WILL return and the variable
        // msg will be filled with interesting details
        // about exactly what the user did to the window.

        TranslateMessage( &msg );   // translates 
        // the message so WndProc can process it
        // more easily.

        // Next we 'dispatch' the message, or
        // send it off to WndProc for processing.

        // Notice that there is NO EXPLICIT function
        // call to WndProc, but somehow in the bowels
        // of the Windows O/S, calling DispatchMessage
        // WILL result in a call to your WndProc function,
        // WITH the appropriate msg struct passed in
        // as well.
        
        DispatchMessage( &msg );    // this line RESULTS IN
        // a call to WndProc(), passing the message and
        // the HWND.


    }
    #pragma endregion

    return msg.wParam;    // return from WinMain
}

LRESULT CALLBACK WndProc(   HWND hwnd,      // "handle" to the window that this message is for
                            UINT message,   // TYPE of message (e.g. WM_PAINT is a message asking to paint the window)
                            WPARAM wparam,  // information about the actual message
                            LPARAM lparam ) // MORE info about the message
{
    // If WinMain was the heart of the Windows application, then
    // WndProc is the soul.

    // WndProc does just 1 thing:
    //    - Execute some bit of code in response
    //      to user interactions with our windows
    //      application.  

    // The tricky bit about WndProc is that NOWHERE IN THIS APP'S
    // CODE DO YOU EVER SEE ANY EXPLICIT FUNCTION CALLS
    // TO WndProc!!!  Does that mean WndProc never
    // gets used???

    // NO!!!  Take a look again, around where
    // we create the WNDCLASS.

    // Notice, how the WNDCLASS has lpfnWndProc = WndProc??
    // THAT is the reference to this function.

    // The WINDOWS O/S PERFORMS the function call to
    // WndProc when we call DispatchMessage().

    short AppCommand = 0;

    switch( message )
    {
    case WM_CREATE:
        // upon creation, let the speaker beep at 50Hz, for 10ms.
        Beep( 50, 10 );
        return 0;
        break;

    case WM_PAINT:
        {
            // we would place our Windows painting code here.
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint( hwnd, &ps );

            // draw a circle and a 2 squares
            Ellipse( hdc, 20, 20, 160, 160 );
            Rectangle( hdc, 50, 50, 90, 90 );
            Rectangle( hdc, 100, 50, 140, 90 );
            
            EndPaint( hwnd, &ps );
        }
        return 0;
        break;

    case WM_APPCOMMAND:
        AppCommand = GET_APPCOMMAND_LPARAM(lparam);
        switch (AppCommand)
        {
        case APPCOMMAND_MEDIA_NEXTTRACK:
            printf("{\"action\":\"next\"}\n");
            break;
        case APPCOMMAND_MEDIA_PLAY_PAUSE:
            printf("{\"action\":\"play\"}\n");
            break;
        case APPCOMMAND_MEDIA_PREVIOUSTRACK:
            printf("{\"action\":\"back\"}\n");
            break;
        case APPCOMMAND_MEDIA_STOP:
            break;
        }
        return 0;
        break;


    case WM_DESTROY:
        PostQuitMessage( 0 ) ;
        return 0;
        break;

        
    }

    // Now, try going into Visual Studio and
    // press WM_ then press CTRL + SPACE.

    // Or go to
    // http://msdn2.microsoft.com/en-us/library/ms632595.aspx

    // See that huge listing?  Those are ALL THE EVENTS
    // that Windows could possibly throw at our application.
    // WOW!  That's a lot of events.  WE don't want to 
    // have to write code for every single one of them!
    // But our WndProc gets called whenever ANY event
    // happens to our application.  What do we do with
    // the events we don't want to handle?
    
    // Simple.  We will pass the events we DON'T want
    // to handle to DefWindowProc().  DefWindowProc()
    // knows what to do with the events we don't want
    // to handle so that our application remains stable
    // and good.
    return DefWindowProc( hwnd, message, wparam, lparam );
}



/// GLOSSARY ///
// HINSTANCE:  "Handle" to an instance.  Every running INSTANCE
// of an application has a handle to it that is YOUR MEANS
// by which to manipulate, talk about, or refer to that specific
// application instance as it exists inside the Windows O/S.

// What's an instance again?  If you have 2 copies of the same programming running
// at the same time, then you are running 2 INSTANCES
// of the same program (2 copies of Microsoft Word, for example).
// Each INSTANCE of a program has its own INSTANCE HANDLE and
// hence its PID (ProcessID - unique integer identifier
// for each program that is currently running in the Windows O/S)
// and its own entry in the Window task manager.

// TRY THIS:  Press CTRL+ALT+DEL to bring up the Windows
// Task Manager.
    // Now switch to the PROCESSES tab.
    // Click the "IMAGE NAME" column, so that everything gets organized by name of the process.
    // Now, open NOTEPAD, 3 times.  You should have 3 Notepad windows open.
    // NOW, LOOK AT the Windows Task Manager.  Try to locate __3__ entries
    // that say NOTEPAD.EXE.  Open a fourth notepad.  Open a fifth notepad.
    // every instance of notepad you open gets its own entry in that table.

// Now HINSTANCE is exactly what it sounds like . . its a "handle"
// (a means by which to access or control) the INSTANCE of your
// program.
//
// The actual INSTANCE of your application lives inside the Windows O/S.
// But you have a HANDLE TO IT, and your HANDLE to it is your means
// by which to manipulate it, refer to it, change it, or delete it.

// HWND:  HANDLE TO A WINDOW.  This is exactly the same in CONCEPT as
//        the INSTANCE HANDLE, but now, this is a handle TO THE WINDOW ITSELF.
//        The HANDLE TO THE WINDOW is your means by which to change
//        manipulate, or refer to the window that belongs to your program.
//        A single INSTANCE of an application can have MULTIPLE window
//        handles associated with it.  THAT IS WHY when you CREATE A WINDOW,
//        using the CreateWindow() function, you MUST PASS the hInstance
//        parameter.  That is so that Windows knows which application
//        INSTANCE is attached to which WINDOW.
//
// HDC:  HANDLE TO A DEVICE CONTEXT.  Hmm.  I'm not going to explain this
//       in detail here, because we're not really using the HDC much
//       in this example.  Perhaps at a later time.


///////////////////////////
// THERE, ALL DONE - CLOSING NOTES.
// Everyone knows starting Windows Programming can be a bit hard.
// There are a few things I'd like to highlight here.
//
// Now you might be wondering, "ok, if WinMain is the application
// starting point, WHERE / WHEN / HOW does WinMain accept
// PARAMETERS?"
//
// To understand this, you must start to see your "Windows program"
// as really just a FUNCTION that Windows will call, when it is
// time to start up your application.
// 
// So where do the values of hInstance, hPrevInstance, szCmdLine
// and iCmdShow come from?
// These parameters are PASSED BY the Windows O/S AT APPLICATION START TIME.
// So all of hInstance, hPrevInstance (which is always passed as NULL)
// szCmdLine and iCmdShow are passed by the Windows O/S
// to your application.

////////////////////
// Understanding what szCmdLine is and does:
//
// Do me a favor.
// Open the Windows command prompt (go to START->Run,
// then type "cmd" in the box that appears there.)
//
// You should see a black console window, like the one that your basic console C++ 
// apps run in.  In the black window, type in:
//          explorer
// then press enter.

// What should happen is your windows file explorer should pop up.

// Now go back to the command prompt and type in
//          explorer "C:\Program Files"

// Notice now that the Windows disk explorer now opens in the folder "C:\Program Files"
// In the above example, "C:\Program Files" is a command line argument that modifies
// the behaviour of the disk explorer upon its launch.

// So the explorer.exe program is a Windows program.
// And szCmdLine WOULD BE WHERE YOU TAKE that extra string
// that is passed to the program at the time the program is
// launched.

// You won't necessarily use this at all in your programming!
// But, it is good to know.


// REFERENCES:
// If you want to know more about Windows Programming
// in this CLASSIC C++ way, then you should pick
// up a copy of Charles Petzold's "Programming Windows,
// 5th Edition"
// http://www.charlespetzold.com/pw5/
// On Amazon:  http://www.amazon.com/exec/obidos/ISBN=157231995X

// "The Petzold" is THE reference that all the game
// books out there (some of which are pretty good!)
// draw on when they write their Win32 chapter (its
// obvious from the way they've written them!)

// What's annoying is, a lot of the people who write
// those books though, never acknowledge Petzold or
// mention where they derived their Win32 understanding
// from.

// So, the Petzold is where I got my initial understanding
// anyway, and its really good.  Check it out
// from your library if you haven't the $.

// More refs:
// MSDN:  "About messages and message queues"
// http://msdn2.microsoft.com/en-us/library/ms644927(VS.85).aspx

////////////////
// MORE Closing notes:
// This is sometimes called "EVENT DRIVEN
// PROGRAMMING" -- the idea is that your
// program is entirely driven by EVENTS.
// If there are no events, then your
// Windows program DOES NOTHING.

// Note that this is NOT the case with GAMES!
// GAMES CAN'T WAIT!  Games must be fast.
// For games, you would use DirectInput,
// and things like that, and you WOULD NOT
// be WAITING for messages.  Instead,
// you want to be DIRECTLY listening
// at the keyboard and mouse for user 
// interaction with those DEVICES.


///////////////////
// You MIGHT HAVE been wondering about
// the apparent RETURN TYPE of WinMain and
// WndProc.

// Looking at those function prototypes, we have:

/*

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow );
LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );

*/

// For example, a question you might have might be:
// WHY is the return type of WinMain "int WINAPI"?
// That is so weird.

// The short answer, is ITS NOT!!

// The return type of WinMain is just INT.
// "WINAPI" IS NOT PART OF THE RETURN TYPE
// OF THE WinMain FUNCTION!

// The second word after the return type
// (WINAPI) is called the CALLING CONVENTION of
// the function.

// In case you're still interested, check out
// these links:
// http://support.microsoft.com/kb/100832
// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vccore98/html/_core_calling_conventions_topics.asp
// http://www.devnewz.com/devnewz-3-20050125UsingWin32CallingConventions.html

// A MSDN basic window example:
// http://msdn2.microsoft.com/en-us/library/aa383668(VS.85).aspx

// MSDN root page for a lot of windows stuff
// http://msdn2.microsoft.com/en-us/library/ms632586(VS.85).aspx

/* 
     ____   __   __      __   __  ___
    / _  \ /  / /  /    /  /  \ \/  /
   / _/ / /  / /  /    /  /    \   /
  / _/ \ /  / /  /__  /  /__   /  /
 /_____//__/ /______//______/ /__/

*/