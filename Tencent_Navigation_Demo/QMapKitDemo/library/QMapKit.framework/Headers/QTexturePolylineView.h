//
//  QTexturePolylineView.h
//  QMapKit
//
//  Created by fan on 2017/7/13.
//  Copyright © 2017年 tencent. All rights reserved.
//

#import "QPolylineView.h"

/**
 * @brief QTexturePolylineView中各个子线段的样式定义
 */
@interface QSegmentStyle : NSObject

/**
 * @brief 本线段的起始坐标点在坐标点串(QPolyline.points)的下标. 从0开始
 */
@property (nonatomic, assign) int   startIndex;
/**
 * @brief 本线段的终点坐标点在坐标点串(QPolyline.points)的下标
 */
@property (nonatomic, assign) int   endIndex;
/**
 * @brief 本线段就显示的颜色下标。代表styleTextureImage图片或默认图片的所采用的行(1像素为单位)
 */
@property (nonatomic, assign) int   colorImageIndex;

@end

/**
 * @brief QTexturePolylineView中纹理的使用方式
 */
typedef NS_ENUM(NSInteger, QTextureLineDrawType) {
    QTextureLineDrawType_SliceAsBackground = 0, // 将图片以1像素为单位按行切片，根据下标从图片选取1像素来绘制线路样式(最大支持16像素高)
    QTextureLineDrawType_RepeatDraw,            // 重复绘制整个图片
    QTextureLineDrawType_FootPrint              // 以足迹的形式重复绘制整个图片
};

/**
 * @brief 具有丰富显示样式的线覆盖物
 *
 * 默认在POI之下. 
 * 采用纹理图片绘制线，因此父类中的strokeColor, borderColor, borderWidth, lineDashPattern等不再有效
 *
 */
@interface QTexturePolylineView : QPolylineView

/**
 * @brief 定义了各子线段的样式(比如为每个线段定义不同的颜色). 不可为nil
 */
@property (nonatomic, copy) NSArray<QSegmentStyle *> *segmentStyle;

/**
 * @brief 图片styleTextureImage的绘制方式. 默认为QTextureLineDrawType_SliceAsBackground
 */
@property (nonatomic, assign) QTextureLineDrawType drawType;

/**
 * @breif 绘制线所采用的纹理。为nil时则采用默认样式的纹理
 *
 * 当QTextureLineDrawType_SliceAsBackground时, 要求图片为以1像素为单位的多行的图片.样例参照color_texture.png图片
 */
@property (nonatomic, strong) UIImage  *styleTextureImage;

/**
 * @brief footprints之间的间距。 单位：Point
 *
 * 仅当TextureLineDrawType_FootPrint时有效
 */
@property (nonatomic, assign) CGFloat   footprintStep;

/**
 * @brief 是否绘制箭头图标
 *
 * 仅当QTextureLineDrawType_SliceAsBackground时有效
 */
@property (nonatomic, assign, getter=isDrawSymbol) BOOL   drawSymbol;

/**
 * @breif 箭头图标。默认采用默认样式箭头
 *
 * 仅当QTextureLineDrawType_SliceAsBackground时有效
 */
@property (nonatomic, strong) UIImage  *symbolImage;

/**
 * @breif 箭头之间的间距
 *
 * 仅当QTextureLineDrawType_SliceAsBackground时有效
 */
@property (nonatomic, assign) CGFloat   symbolGap;

/**
 * @brief 路线擦除功能，将从起点开始到coordinate坐标的路线颜色置灰或擦除
 *
 * @param coordinate 被擦除的终点坐标
 * @param pointIndex 终点所在子线段起点的下标
 * @param clearColor yes则擦除 no则置灰
 *
 * 需要QTextureLineDrawType_SliceAsBackground 且 styleTextureImage为nil
 */
- (void)eraseFromStartToCurrentPoint:(CLLocationCoordinate2D)coordinate searchFrom:(int)pointIndex toColor:(BOOL)clearColor;

@end

/**
 * @brief 导航线相关的接口
 */
@interface QTexturePolylineView (Navigation)

/**
 * @brief 设置转向箭头的位置
 *
 * @note 箭头的显示级别为QOverlayLevelAboveRoads
 */
- (void)setTurnArrowAtSegmentIndex:(int)index;

/**
 * @brief 隐藏转向箭头
 */
- (void)clearTurnArrow;

/**
 * @brief 设置转向箭头的样式, 所有线共享一个样式
 */
- (void)setTurnArrowColor:(UIColor*)filler borderColor:(UIColor*)border;

@end

