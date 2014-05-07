//
//  FMMediaKeyDelegate.m
//  Media Keys Handler
//
//  Created by Michael Feldstein on 12/29/13.
//  Copyright (c) 2013 Michael Feldstein. All rights reserved.
//

#import "FMMediaKeyDelegate.h"
#import "SPMediaKeyTap.h"

#include <stdio.h>

@implementation FMMediaKeyDelegate

- (void) sendMessage:(NSString*)msg {
    NSString* json = [NSString stringWithFormat:@"{\"action\":\"%@\"}\n", msg];
    const char* utf8 = [json UTF8String];
    unsigned long len = strlen(utf8);
    // Write out 4 bytes of the message length, followed by the message.
    fprintf(stdout, "%c%c%c%c%s",
            (char) (len & 0xff),
            (char) ((len>>8) & 0xFF),
            (char) ((len>>16) & 0xFF),
            (char) ((len>>24) & 0xFF),
            utf8);
    
    fflush(stdout);
}

-(void)mediaKeyTap:(SPMediaKeyTap*)keyTap receivedMediaKeyEvent:(NSEvent*)event
{
	assert([event type] == NSSystemDefined && [event subtype] == SPSystemDefinedEventMediaKeys);
    
	int keyCode = (([event data1] & 0xFFFF0000) >> 16);
	int keyFlags = ([event data1] & 0x0000FFFF);
	int keyState = (((keyFlags & 0xFF00) >> 8)) == 0xA;
	if (keyState == 1) {
		switch (keyCode) {
			case NX_KEYTYPE_PLAY:
                [self sendMessage:@"play"];
				return;
			case NX_KEYTYPE_FAST:
                [self sendMessage:@"next"];
                return;
			case NX_KEYTYPE_REWIND:
                [self sendMessage:@"back"];
                return;
		}
	}
}

@end
