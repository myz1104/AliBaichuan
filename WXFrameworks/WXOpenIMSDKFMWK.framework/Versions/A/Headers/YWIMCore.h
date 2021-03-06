//
//  YWIMCore.h
//
//
//  Created by huanglei on 14/12/11.
//  Copyright (c) 2014年 taobao. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "YWServiceDef.h"
#import "YWAPI.h"

@protocol IYWLoginService, IYWConversationService;
@protocol IYWExtensionService;
@protocol IYWUIService;
@protocol IYWTribeService;
@protocol IYWRoamingService;
@protocol IYWSettingService;

#pragma mark - 常量定义

/**
 *  SDK类型
 */
typedef enum : NSUInteger {
    /// 淘宝账号体系（与旺旺消息互通）
    YWSDKTypeTaobao,
    /// 自由账号体系（App之间消息隔离）
    YWSDKTypeFree,
} YWSDKType;

/**
 *  用户上下文，可以从上下文中获得服务
 */
@interface YWIMCore : NSObject



#pragma mark - prepare

/**
 *  WXOBaseContext对象在使用之前需要先进行初始化。
 *  @param aSDKType SDK类型，根据使用的账号体系不同，详见：WXOSDKType 的定义
 */
- (void)prepareWithSdkType:(YWSDKType)aSDKType;

/// 是否已经初始化
@property (nonatomic, assign, readonly) BOOL prepared;

/**
 *  监听一个BaseContext prepared完成
 */
typedef void(^YWBaseContextPreparedBlock)(YWIMCore *aBaseContext);

/**
 *  监听一个BaseContext prepared完成
 *  @param aKey 用来区分不同的监听者，一般可以使用监听对象的description
 *  @param aPriority 有多个监听者时，调用的优先次序。开发者一般设置：YWBlockPriority
 */
- (void)addBaseContextPreparedBlock:(YWBaseContextPreparedBlock)aBlock forKey:(NSString *)aKey priority:(YWBlockPriority)aPriority;

/**
 *  移除一个BaseContext prepared完成的监听
 */
- (void)removeBaseContextPreparedBlockForKey:(NSString *)aKey;


#pragma mark - 获取服务

/**
 *  获取长连接服务
 */
- (id<IYWLoginService>)getLoginService;

/**
 *  获取会话相关服务
 */
- (id<IYWConversationService>)getConversationService;

/**
 *  获取扩展服务
 */
- (id<IYWExtensionService>)getExtensionService;


/**
 *  群相关服务
 */
- (id<IYWTribeService>)getTribeService;

/**
 *  漫游相关服务
 */
- (id<IYWRoamingService>)getRoamingService;

/**
 *  各种设置项
 */
- (id<IYWSettingService>)getSettingService;

#pragma mark - 状态读取

/// SDK类型
@property (nonatomic, assign, readonly) YWSDKType sdkType;

@end

@protocol IYWPushService;

@interface YWIMCore ()

#pragma mark - deprecated 已废弃


+ (instancetype)sharedInstance __attribute__((unavailable("通过WXOSdk的fetchNewBaseContext来获取，详见该函数注释")));


- (void)prepareWithAppKey:(NSString *)aAppKey
       networkEnvironment:(YWEnvironment)aNetworkEnvironment
                  sdkType:(YWSDKType)aSDKType __attribute__((unavailable("use prepareWithSdkType: instead")));

- (id<IYWPushService>)getPushService __attribute__((unavailable("use WXOSdk的getGlobalPushService方法")));

- (id<IYWUIService>)getUIService __attribute__((deprecated("如果您基于OpenIM的UI接口进行开发，您不需要再获取YWIMCore实例，您可以直接从YWAPI中使用fetchIMKitForOpenIM方法获取YWIMKit并持有该实例，详见注释")));;


@end
