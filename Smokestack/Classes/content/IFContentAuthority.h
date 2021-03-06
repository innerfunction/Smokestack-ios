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
#import "IFCompoundURI.h"
#import "IFContentPath.h"

@class IFContentProvider;
@protocol IFContentAuthority;

/**
 * A class providing functionality for writing responses to content URL and URI requests.
 */
@protocol IFContentAuthorityResponse <NSObject>

/**
 * Respond with content data.
 * Writes the response data in full and then ends the response.
 */
- (void)respondWithData:(NSData *)data mimeType:(NSString *)mimeType cachePolicy:(NSURLCacheStoragePolicy)policy;
/// Start a content response. Note that the [done] method must be called on completion.
- (void)respondWithMimeType:(NSString *)mimeType cacheStoragePolicy:(NSURLCacheStoragePolicy)policy;
/**
 * Write content data to the response.
 * The response must be started with a call to the [respondWithMimeType: cacheStoragePolicy:] method before
 * this method is called. This method may then be called as many times as necessary to write the content data
 * in full. The [done] method must be called once all data is written.
 */
- (void)sendData:(NSData *)data;
/// End a content response.
- (void)done;
/// Respond with string data of the specified MIME type.
- (void)respondWithStringData:(NSString *)data mimeType:(NSString *)mimeType cachePolicy:(NSURLCacheStoragePolicy)cachePolicy;
/// Respond with JSON data.
- (void)respondWithJSONData:(id)data cachePolicy:(NSURLCacheStoragePolicy)cachePolicy;
/// Respond with file data of the specified MIME type.
- (void)respondWithFileData:(NSString *)filepath mimeType:(NSString *)mimeType cachePolicy:(NSURLCacheStoragePolicy)cachePolicy;
/**
 * Respond with an error indicating why the request couldn't be resolved.
 * This method should be called instead of one of the respondWithMimeType* methods defined on this protocol, whenever
 * an error occurs that prevents the request data from being resolved. Calling this method completes the response.
 */
- (void)respondWithError:(NSError *)error;

@end

@protocol IFContentAuthorityPathRoot <NSObject>

/**
 * Resolve content data for the specified authority, path and parameters, and write the result to the provided
 * response object.
 */
- (void)writeResponse:(id<IFContentAuthorityResponse>)response
         forAuthority:(id<IFContentAuthority>)authority
                 path:(IFContentPath *)path
           parameters:(NSDictionary *)parameters;

@end

/**
 * A protocol to be implemented by containers which are capable of providing data to content URIs and URLs.
 */
@protocol IFContentAuthority

/// The content provider the authority belongs to.
@property (nonatomic, weak) IFContentProvider *provider;

/// Handle an NSURLProtocol originating request.
- (void)handleURLProtocolRequest:(NSURLProtocol *)protocol;
/// Cancel an NSURLProtocol request currently being processed by the container.
- (void)cancelURLProtocolRequest:(NSURLProtocol *)protocol;
/// Return content for an internal content URI.
- (id)contentForPath:(NSString *)path parameters:(NSDictionary *)parameters;
/// Write a content reponse for the specified path.
- (void)writeResponse:(id<IFContentAuthorityResponse>)response
              forPath:(IFContentPath *)path
           parameters:(NSDictionary *)parameters;


@end

NSError *makePathNotFoundResponseError(NSString *path);

NSError *makeInvalidPathResponseError(NSString *path);

NSError *makeUnsupportedTypeResponseError(NSString *type);

