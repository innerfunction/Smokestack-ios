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
//  Created by Julian Goacher on 09/12/2015.
//  Copyright © 2015 InnerFunction. All rights reserved.
//

#import "IFCommandProtocol.h"
#import "NSDictionary+IF.h"
#import "NSString+IF.h"

@implementation IFCommandProtocol

- (id)init {
    self = [super init];
    if (self) {
        _commands = [NSDictionary dictionary];
    }
    return self;
}

- (NSArray *)supportedCommands {
    return [_commands allKeys];
}

- (void)addCommand:(NSString *)name withBlock:(IFCommandProtocolBlock)block {
    _commands = [_commands dictionaryWithAddedObject:block forKey:name];
}

- (NSString *)qualifyName:(NSString *)name {
    return [NSString stringWithFormat:@"%@.%@", _commandPrefix, name ];
}

- (NSDictionary *)parseArgArray:(NSArray *)args argOrder:(NSArray *)argOrder defaults:(NSDictionary *)defaults {
    NSMutableDictionary *result = [[NSMutableDictionary alloc] initWithDictionary:defaults];
    NSString *name = nil;
    id value = nil;
    NSInteger position = 0;
    // Iterate over each argument.
    for (id arg in args) {
        NSString *strarg = nil;
        if ([arg isKindOfClass:[NSString class]]) {
            strarg = (NSString *)arg;
        }
        // If argument starts with - then it is a switch.
        if ([strarg hasPrefix:@"-"]) {
            // If we already have a name then it indicates a valueless switch; map the switch name to binary true.
            if (name) {
                result[name] = @1;
            }
            // Subtract the - prefix from the switch name.
            name = [strarg substringFromIndex:1];
        }
        // We have switch name so next argument is the value.
        else if (name) {
            value = arg;
        }
        // No switch specified so use argument position to read name.
        else if (position < [argOrder count]) {
            name = argOrder[position++];
            value = arg;
        }
        // If we have a name and value then map them into the result.
        if (name && value != nil) {
            result[name] = value;
            name = nil;
            value = nil;
        }
    }
    return result;
}

#pragma mark - IFCommand protocol

- (QPromise *)execute:(NSString *)name withArgs:(NSArray *)args {
    // Split the protocol prefix from the name to get the actual command name.
    NSArray *nameParts = [name split:@"\\."];
    NSString *commandName = [nameParts objectAtIndex:1];
    // Find a handler block for the named command.
    IFCommandProtocolBlock block = [_commands objectForKey:commandName];
    if (block) {
        return block( args );
    }
    // No handler found.
    return [Q reject:[NSString stringWithFormat:@"Unrecognized command name: %@", commandName]];
}

@end
