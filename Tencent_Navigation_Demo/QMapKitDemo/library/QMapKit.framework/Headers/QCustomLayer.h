//
//  QCustomLayer.h
//  QMapKit
//
//  Created by fan on 2019/10/10.
//  Copyright © 2019 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
* @brief 用于自定义图层的类
*/
@interface QCustomLayer : NSObject

/**
* @brief 图层的唯一标识. 在个性化图层编辑平台成功上传图层时得到的其标识字符串
*/
@property (nonatomic, copy ) NSString   *layerID;

@end

NS_ASSUME_NONNULL_END
