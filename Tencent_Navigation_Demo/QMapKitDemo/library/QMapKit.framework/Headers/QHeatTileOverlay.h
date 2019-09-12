//
//  QHeatTileOverlay.h
//  QMapKit
//
//  Created by tabsong on 15/8/10.
//  Copyright (c) 2015年 Tencent. All rights reserved.
//

#import "QTileOverlay.h"
#import "QHeatTileNodeProtocol.h"

#pragma mark - QHeatTileGradient

/**
 * @brief 热力图渐变属性
 */
@interface QHeatTileGradient : NSObject

/**
 * @brief 颜色变化数组
 */
@property (nonatomic, readonly) NSArray<UIColor *> *colors;

/**
 * 颜色变化节点，需为严格递增数组，区间为[0, 1.0]
*/
@property (nonatomic, readonly) NSArray<NSNumber *> *startPoints;

/**
 * @brief 重新设置gradient的时候，需要执行 QTileOverlayView 的 reloadData 方法重刷新渲染缓存。
 * @param colors      颜色列表
 * @param startPoints 颜色变化节点列表，需为严格递增数组(无相同值)，区间为[0, 1.0]
 * @return QHeatTileGradient
 *
 * @notes colors和startPoints的个数必须相同
 */
- (instancetype)initWithColor:(NSArray<UIColor *> *)colors andWithStartPoints:(NSArray<NSNumber *> *)startPoints;

@end

#pragma mark - QHeatTileOverlay

/**
 *  @brief  热力图overlay
 *
 */
@interface QHeatTileOverlay : QTileOverlay

/**
 *  @brief  生成热力图overlay
 *
 *  @param heatTileNodes 热力图节点元素数组, 每个元素符合 QHeatTileNodeProtocol 协议
 *  @return heatTileOverlay
 */
- (instancetype)initWithHeatTileNodes:(NSArray *)heatTileNodes;

/**
 *  @brief  热力图数据: 原始的节点数据. 数组每个元素符合 QHeatTileNodeProtocol 协议
 *
 *  在添加完后设值时需要执行 QHeatTileOverlayView 的 reloadData 方法重刷新渲染缓存
 */
@property (nonatomic, copy ) NSArray<id<QHeatTileNodeProtocol> > *nodes;

/**
 *  @brief  热力图样式: 衰变半径. 单位 point
 *
 *  范围越大计算耗时越长。默认20. 建议100以内
 *  在添加完后设值时需要执行 QHeatTileOverlayView 的 reloadData 方法重刷新渲染缓存
 */
@property (nonatomic, assign ) NSInteger decayRadius;

/**
 *  @brief  热力图样式: 透明度. 默认为0.6，范围：0-1
 *
 *  在添加完后设值时需要执行 QHeatTileOverlayView 的 reloadData 方法重刷新渲染缓存
 */
@property (nonatomic, assign) CGFloat opacity;

/**
 *  @brief  热力图样式: 颜色梯度
 *
 *  在添加完后设值时需要执行 QHeatTileOverlayView 的 reloadData 方法重刷新渲染缓存
 */
@property (nonatomic, strong) QHeatTileGradient *gradient;

@end

