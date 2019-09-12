//
//  QTileOverlay.h
//  QMapKit
//
//  Created by tabsong on 2017/6/27.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QGeometry.h"
#import "QOverlay.h"

/**
 * @brief 代表单个瓦片的索引
 */
typedef struct {
    NSInteger x;    ///< 瓦片的x下标
    NSInteger y;    ///< 瓦片的y下标
    NSInteger z;    ///< 瓦片所在缩放级别
    NSInteger     language;       // language. 1:en, 0:zh
    CGFloat contentScaleFactor; ///< 暂不支持
} QTileOverlayPath;

/**
 * @brief 用于自定义瓦片数据的类
 */
@interface QTileOverlay : NSObject <QOverlay>
{
    @package
    QMapRect _boundingRect;     //当前仅返回全球范围外接矩形
}

/**
 * @brief QTileOverlay 的构造函数.
 *
 * @param URLTemplate tile的URL格式.URL格式请参照苹果MKTileOverlay接口格式
 *
 *  URL template is a string where the substrings "{x}", "{y}", "{z}", and "{scale}" are replaced with values
 *  from a tile path to create a URL to load. For example: http://server/path?x={x}&y={y}&z={z}&scale={scale}
 */
- (instancetype)initWithURLTemplate: (NSString *)URLTemplate;

/**
 *  @brief tile的URL格式
 */
@property (readonly) NSString *URLTemplate;

/**
 *  @brief  resolution=512x512 or 256x256
 */
@property (nonatomic, assign) BOOL isHighResoultionTile;

/**
 *  @brief  自定义瓦片的自定义存储目录，如不设置则不使用缓存
 */
@property (nonatomic, strong) NSString *tileCacheDir;

@end

/**
 * @brief QTileOverlay的扩展类，用于提供数据加载方法
 */
@interface QTileOverlay (CustomLoading)

/**
 *  @brief  tile 的URL
 *
 *  @param path     path
 *
 *  有可能子线程调用.  子类重载时不需要调用super
 */
- (NSURL *)URLForTilePath:(QTileOverlayPath)path;

/**
 *  @brief  加载tileOverlay函数 (调用URLForTilePath 获取URL 启动内部的异步网络数据加载)
 *
 *  @param path tile 的索引
 *
 *  开发者可在子类重载实现来满足自定义功能。有可能子线程调用.  子类重载时不需要调用super
 */
- (void)loadTileAtPath:(QTileOverlayPath)path result:(void (^)(NSData *tileData, NSError *error))result;

/**
 *  @brief  取消本瓦片下载. 当地图显示区域发生变化时，会取消显示区域外的瓦片的下载.
 *
 *  有可能子线程调用.  子类重载时不需要调用super
 *  已cancel的瓦片请不要再调用loadTileAtPath:result中的result回调
 */
- (void)cancelLoadOfTileAtPath:(QTileOverlayPath)tilePath;

@end

