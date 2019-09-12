//
//  TNKAudioPlayer.h
//  TNKNavigationKit
//
//  Created by 薛程 on 2018/12/10.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

@class TNKAudioPlayer;

/**
 *  @brief  内置语音播报器事件回调.
 */
@protocol TNKAudioPlayerDelegate <NSObject>

/**
 *  @brief  播报完成回调.
 *  @param player 内置语音播报器.
 */
- (void)audioPlayerDidFinishPlaying:(TNKAudioPlayer *)player;

@end

/**
 *  @brief  内置语音播报器. 只可在真机环境使用.
 */
@interface TNKAudioPlayer : NSObject

/**
 *  @brief  获取内置语音播放器实例.
 */
+ (instancetype)sharedAudioPlayer;

/**
 *  @brief  TNKAudioPlayer的回调. 用于接收播报状态等事件.
 */
@property (nonatomic, weak) id <TNKAudioPlayerDelegate> delegate;

/**
 *  @brief  语音播报器是否在播放状态.
 */
@property (nonatomic, readonly) BOOL isPlaying;

/**
 *  @brief  调用语音播报器播放预置文案内容. 预制文案的播报优先级高于导航语音播报, 调用该方法会打断正在播放的导航语音.
 *  @param type 播报类型. 具体文案如下:
 *  1: 开始接单了
 *  2: 停止接单了
 *  3: 您有新的订单，请及时查看
 *  4: 现在去接乘客上车
 *  5: 已接到乘客
 *  6: 行程开始，请您提醒乘客系好安全带
 *  7: 夜间行驶，请您注意行车安全，平台将实时保护司乘安全
 *  8: 已到达目的地，乘客开门时提醒注意后方来车
 *  9: 请提醒乘客完成支付再下车
 */
- (void)playWithText:(int)type;

/**
 *  @brief  停止当前播报内容.
 */
- (void)stop;

@end
