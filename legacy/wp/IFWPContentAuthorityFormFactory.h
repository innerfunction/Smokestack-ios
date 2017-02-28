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
//  Created by Julian Goacher on 16/02/2016.
//  Copyright © 2016 InnerFunction. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IFIOCObjectFactoryBase.h"
#import "IFURIHandling.h"
#import "IFViewBehaviourObject.h"

@class IFWPContentAuthority;

@interface IFWPContentAuthorityFormFactory : IFIOCObjectFactoryBase {
    NSDictionary *_stdParams;
    NSUserDefaults *_userDefaults;
}

@property (nonatomic, weak) IFWPContentAuthority *container;

@end

@interface IFWPContentLoginBehaviour : IFViewBehaviourObject

- (id)initWithContainer:(IFWPContentAuthority *)container loginAction:(NSString *)loginAction;

@property (nonatomic, weak) IFWPContentAuthority *container;
@property (nonatomic, strong) NSString *loginAction;

@end