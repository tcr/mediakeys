//
//  StdinListener.m
//  Media Keys Handler
//
//  Created by Michael Feldstein on 1/12/14.
//  Copyright (c) 2014 Michael Feldstein. All rights reserved.
//

#import "StdinListener.h"

@implementation StdinListener

- (id)init {
    self = [super init];
    if (self) {
        _stdin = [NSFileHandle fileHandleWithStandardInput];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(dataRead:) name:NSFileHandleReadCompletionNotification object:_stdin];
        [_stdin readInBackgroundAndNotify];
    }
    return self;
}

- (void)dataRead:(NSNotification*)notification
{
    // Currently the only message we get sent is a quit message
    // No need to check what it was yet...
    exit(0);
}

@end
