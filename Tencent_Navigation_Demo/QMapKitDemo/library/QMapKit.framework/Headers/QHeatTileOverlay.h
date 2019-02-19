//
//  QHeatTileOverlay.h
//  QMapKit
//
//  Created by tabsong on 15/8/10.
//  Copyright (c) 2015年 Tencent. All rights reserved.
//

#import "QTileOverlay.h"
#import "QHeatTileNodeProtocol.h"

/**
 *  @brief  热力图overlay
 *
 */
@interface QHeatTileOverlay : QTileOverlay

/**
 *  @brief  生成热力图overlay, 默认的衰变半径为26
 *
 *  @param heatTileNodes 热力图节点元素数组, 每个元素符合 QHeatTileNodeProtocol 协议
 *  @return heatTileOverlay
 */
- (instancetype)initWithHeatTileNodes:(NSArray *)heatTileNodes;

/**
 *  @brief  生成热力图overlay
 *
 *  @param heatTileNodes 热力图节点元素数组, 每个元素符合 QHeatTileNodeProtocol 协议
 *  @param decayRadius 衰变半径, 超过30会影响效率, 参数若 <= 0, 会使用默认值26
 *  @return heatTileOverlay
 */
- (instancetype)initWithHeatTileNodes:(NSArray *)heatTileNodes decayRadius:(NSInteger)decayRadius NS_DESIGNATED_INITIALIZER;

/**
 *  @brief  衰变半径
 */
@property (nonatomic, readonly) NSInteger decayRadius;

/**
 *  @brief  更新热力图节点数据(全部更新)
 *
 *  @param heatTileNodes 热力图节点元素数组, 每个元素符合 QHeatTileNodeProtocol 协议
 */
- (void)updateHeatTileNodes:(NSArray *)heatTileNodes;

@end

/**
 * @brief QHeatTileOverlay的扩展类，子类可以重载来配置热力图色盘,用于提供热力度对应的色值
 */
@interface QHeatTileOverlay (CustomColorPalete)

/**
 *  @brief  根据热度值生成颜色.
 *
 *  @param value 热力值
 *  @param outRed    需要填充的red分量
 *  @param outGreen  需要填充的green分量
 *  @param outBlue   需要填充的blue分量
 *  @param outAlpha  需要填充的alpha分量
 */
- (void)colorForValue:(CGFloat)value outRed:(CGFloat *)outRed outGreen:(CGFloat *)outGreen outBlue:(CGFloat *)outBlue outAlpha:(CGFloat *)outAlpha;

@end
