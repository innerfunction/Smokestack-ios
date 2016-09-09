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
//  Created by Julian Goacher on 09/09/2016.
//  Copyright © 2016 InnerFunction. All rights reserved.
//

#import "IFContentPath.h"

@implementation IFContentPath

- (id)initWithPath:(NSArray *)path rootIndex:(NSInteger)rootIdx {
    self = [super init];
    if (self) {
        _path = path;
        _rootIdx = rootIdx;
    }
    return self;
}

- (id)initWithPath:(NSString *)path {
    return [self initWithPath:[path componentsSeparatedByString:@"/"] rootIndex:0];
}

- (id)initWithURL:(NSURL *)url {
    return [self initWithPath:url.path];
}

- (NSString *)root {
    return [self isEmpty] ? nil : _path[_rootIdx];
}

- (IFContentPath *)rest {
    if ([self isEmpty]) {
        return nil;
    }
    return [[IFContentPath alloc] initWithPath:_path rootIndex:_rootIdx + 1];
}

- (NSArray *)components {
    return [_path subarrayWithRange:NSMakeRange(_rootIdx, [_path count] - _rootIdx - 1)];
}

- (BOOL)isEmpty {
    return _rootIdx >= [_path count];
}

- (NSString *)fullPath {
    return [_path componentsJoinedByString:@"/"];
}

@end
