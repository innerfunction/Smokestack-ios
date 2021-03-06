// Copyright 2016 InnerFunction Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//  Created by Julian Goacher on 07/12/2015.
//  Copyright © 2015 InnerFunction. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Q/Q.h>

@class IFCommandScheduler;

@protocol IFCommand <NSObject>

/**
 * Execute the command with the specified name and arguments.
 * Returns a deferred promise which may resolve to an array of new commands to
 * be queued for execution after the current, and any other commands, complete.
 */
- (QPromise *)execute:(NSString *)name withArgs:(NSArray *)args;

@end
