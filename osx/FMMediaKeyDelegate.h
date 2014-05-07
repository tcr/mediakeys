//
//  FMMediaKeyDelegate.h
//  Media Keys Handler
//
//  Created by Michael Feldstein on 12/29/13.
//  Copyright (c) 2013 Michael Feldstein. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FMMediaKeyDelegate : NSObject
- (void) sendMessage:(NSString*)msg;
@end
