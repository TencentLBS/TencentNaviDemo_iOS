//
//  TNKNaviTTS.h
//  TNKNavigation
//
//  Created by Tencent on 2018/3/1.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @brief  声音类型.
 */
typedef enum _TNKNaviTTSVoiceType
{
    TNKNaviTTSVoiceTypeNone    = 0,
    TNKNaviTTSVoiceTypeBeep    = 1,
} TNKNaviTTSVoiceType;

/**
 * @brief  TTS播报内容
 */
@interface TNKNaviTTS : NSObject

/**
* @brief  播报的字符串内容.
*/
@property (nonatomic, strong, nonnull) NSString *ttsString;

/**
 * @brief  声音类型.
 */
@property (nonatomic, assign) TNKNaviTTSVoiceType voiceType;

/**
 * @brief  声音文件路径.
 */
@property (nonatomic, strong, nullable) NSString *voiceFilePath;

/**
 * @brief  TTS内容优先级, 优先级越小越高. 预留字段, 目前不可用.
 */
@property (nonatomic, assign) int priority;

@end
