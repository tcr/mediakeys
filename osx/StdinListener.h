//
//  StdinListener.h
//  Media Keys Handler
//
//  Created by Michael Feldstein on 1/12/14.
//  Copyright (c) 2014 Michael Feldstein. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface StdinListener : NSObject {
    NSFileHandle* _stdin;
}

@end
