//
//  main.m
//  Media Keys Handler
//
//  Created by Michael Feldstein on 12/29/13.
//  Copyright (c) 2013 Michael Feldstein. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "FMMediaKeyDelegate.h"
#import "SPMediaKeyTap.h"
#import "StdinListener.h"

int main(int argc, const char * argv[])
{

    @autoreleasepool {
        FMMediaKeyDelegate* delegate = [[FMMediaKeyDelegate alloc] init];
        SPMediaKeyTap* keyTap = [[SPMediaKeyTap alloc] initWithDelegate:delegate];
        [keyTap startWatchingMediaKeys];
        [delegate sendMessage:@"connected"];
        StdinListener* stdinListener = [[StdinListener alloc] init];
        NSRunLoop* loop = [NSRunLoop currentRunLoop];
        [loop run];
        [stdinListener release];
        [delegate release];
        [keyTap release];
        [loop release];
    }
    return 0;
}

