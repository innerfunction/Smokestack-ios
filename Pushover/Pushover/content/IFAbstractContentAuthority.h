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
//  Created by Julian Goacher on 07/09/2016.
//  Copyright © 2016 InnerFunction. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IFContentAuthority.h"
#import "IFIOCObjectAware.h"
#import "IFIOCConfigurationAware.h"
#import "IFContainer.h"

// TODO Does this class need to extend IFContainer any more?

/**
 * An abstract content authority.
 * This class provides standard functionality needed to service requests from content URLs and URIs. It
 * automatically handles cancellation of NSURLProtocol requests. All requests are forwarded to the
 * [writeResponse: forAuthority: path: parameters:] method, and subclasses should override this method
 * with an implementation which resolves content data as appropriate for the request.
 */
@interface IFAbstractContentAuthority : IFContainer <IFContentAuthority, IFIOCObjectAware, IFIOCConfigurationAware> {
    /// A set of live NSURL responses.
    NSMutableSet *_liveResponses;
}

/// The authority's configuration template. A map of name/value pairs used to configure the authority instance.
@property (nonatomic, strong) NSDictionary *configurationTemplate;
/// A map of configuration parameters.
@property (nonatomic, strong) NSMutableDictionary *configurationParameters;
/// The authority name the class instance is bound to.
@property (nonatomic, strong) NSString *authorityName;
/// A map of addressable path roots. For example, given the path files/all, the path root is 'files'.
@property (nonatomic, strong) NSMutableDictionary *pathRoots;

@end
