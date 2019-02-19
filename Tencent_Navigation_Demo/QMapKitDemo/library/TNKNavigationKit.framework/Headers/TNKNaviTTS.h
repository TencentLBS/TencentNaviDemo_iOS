//
//  TNKNaviTTS.h
//  TNKNavigation
//
//  Created by Tencent on 2018/3/1.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @brief  TTS播报内容
 */
@interface TNKNaviTTS : NSObject

/**
* @brief  播报的字符串内容。
*/
@property (nonatomic,strong)NSString* ttsString;

/**
 * @brief  声音文件路径。
 */
@property (nonatomic,strong)NSString* filePath;

/**
 * @brief  优先级，越小越高。暂时无用，保留。
 */
@property (nonatomic)int priority;

/**
 * @brief  声音文件类型，目前只有叮一声。暂时无用，保留。
 */
@property (assign)int messageType;

@end
