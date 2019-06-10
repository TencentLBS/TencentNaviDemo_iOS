//
//  QIndoorInfo.h
//  QMapKit
//
//  Created by Zhang Tian on 2018/6/12.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @brief 表示室内图的数据类.
 */
@interface QIndoorInfo : NSObject

/**
 * @biref 表示室内图唯一标识楼号.
 */
@property (nonatomic, copy, readonly) NSString *buildUid;

/**
 * @biref 表示室内图楼层.
 */
@property (nonatomic, copy, readonly) NSString *levelName;


/**
 * @brief 初始化 QIndoorInfo.
 *
 * @param buildUid  室内图楼号.
 * @param levelName 室内图楼层.
 * @return QIndoorInfo 对象.
 */
- (instancetype)initWithBuildUid:(NSString *)buildUid levelName:(NSString *)levelName;

@end
