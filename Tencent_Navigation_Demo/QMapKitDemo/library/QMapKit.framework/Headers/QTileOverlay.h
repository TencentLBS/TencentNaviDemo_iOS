//
//  QTileOverlay.h
//  QMapKit
//
//  Created by tabsong on 2017/6/27.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QGeometry.h"

typedef long TileOverlay_priority_t;

// tileOverlay 优先级.
extern const TileOverlay_priority_t TILEOVERLAY_PRIORITY_LOW;
extern const TileOverlay_priority_t TILEOVERLAY_PRIORITY_DEFAULT;
extern const TileOverlay_priority_t TILEOVERLAY_PRIORITY_HIGH;

/**
 * @brief 代表单个瓦片的索引
 */
typedef struct {
    NSInteger x;    ///< 瓦片的x下标
    NSInteger y;    ///< 瓦片的y下标
    NSInteger z;    ///< 瓦片所在缩放级别
    int     language;       // language. 1:en, 0:zh
    char    urlString[256]  DEPRECATED_ATTRIBUTE;
} QTileOverlayPath;

/**
 * @brief 用于自定义瓦片内容的类
 *
 * @notes 请在调用addTileOverlay前设置属性
 */
@interface QTileOverlay : NSObject

/**
 * @brief QTileOverlay 的构造函数. 默认的priority 为TILEOVERLAY_PRIORITY_DEFAULT
 */
- (instancetype)init;

/**
 * @brief QTileOverlay 的构造函数，可以指定优先级.
 *
 *  @param priority 优先级.
 */
- (instancetype)initWithPriority:(TileOverlay_priority_t)priority NS_DESIGNATED_INITIALIZER;

/**
 *  @brief  优先级
 */
@property (nonatomic, assign, readonly) TileOverlay_priority_t priority;

/**
 *  @brief  resolution=512x512 or 256x256
 */
@property (nonatomic, assign) BOOL isHighResoultionTile;

@end

/**
 * @brief QTileOverlay的扩展类，用于提供数据加载方法
 */
@interface QTileOverlay (CustomLoading)

/**
 *  @brief  tile 的URL
 *
 *  @param path     path
 */
- (NSURL *)URLForTilePath:(QTileOverlayPath)path;

/**
 *  @brief  加载tile image (如果该函数返回nil, 则调用URLForTilePath 获取URL 启动内部的异步网络数据加载)
 *
 *  @param path tile 的索引
 *  @return tileImage
 */
- (UIImage *)loadTileImageAtPath:(QTileOverlayPath)path;

/**
 *  @brief  保存tile数据.
 *  @Important: 当 启动内部的异步网络数据加载后, 数据下载成功，才会调用这个函数.
 *
 *  @param tileData tile 数据
 *  @param path     tile 的索引
 */
- (void)saveTileData:(NSData *)tileData atPath:(QTileOverlayPath)path;

@end

