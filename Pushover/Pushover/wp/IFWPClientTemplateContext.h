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
//  Created by Julian Goacher on 15/12/2015.
//  Copyright © 2015 InnerFunction. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IFDB.h"
#import "IFIOCContainerAware.h"
#import "IFWPContentAuthority.h"

/**
 * Data context implementation for the client template.
 * The client template is used to generate post HTML pages using the latest mobile
 * theme. The main purpose of this class is to replace image attachment references
 * with URLs referencing the attachment file in its current location, and to replace
 * post references with appropriate URIs.
 */
@interface IFWPClientTemplateContext : NSObject

- (id)templateContext;
- (id)templateContextForPostData:(NSDictionary *)postData;

@end
