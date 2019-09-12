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
 * @brief 本线段显示的颜色下标。代表styleTextureImage图片或默认图片的所采用的行(1像素为单位)
 *
 * @notes 默认颜色：
 * <table>
 *   <tr><th>色值         <th>颜色
 *   <tr><td>0           <td>灰色
 *   <tr><td>1           <td>深蓝
 *   <tr><td>2           <td>红色
 *   <tr><td>3           <td>黄色
 *   <tr><td>4           <td>绿色
 *   <tr><td>5           <td>淡蓝
 *   <tr><td>6           <td>中蓝
 *   <tr><td>7           <td>透明色
 *   <tr><td>8           <td>灰蓝
 *   <tr><td>9           <td>猪肝红
 * </table>
 *
 * 如果是自定义styleTextureImage则色值代表的颜色与图片相关
 */
@property (nonatomic, assign) int   colorImageIndex;

@end

/**
 * @brief QTexturePolylineView中各个子线段的颜色定义
 */
@interface QSegmentColor : NSObject

/**
 * @brief 本线段的起始坐标点在坐标点串(QPolyline.points)的下标. 从0开始
 */
@property (nonatomic, assign) int   startIndex;
/**
 * @brief 本线段的终点坐标点在坐标点串(QPolyline.points)的下标
 */

@property (nonatomic, assign) int   endIndex;
/**
 * @brief 本线段显示的颜色
 */
@property (nonatomic, strong) UIColor   *color;
/**
 * @brief 本线段显示的描边颜色. 可为nil
 */
@property (nonatomic, strong) UIColor   *borderColor;

@end

#pragma mark - QTexturePolylineView

/**
 * @brief QTexturePolylineView中纹理的使用方式
 *
 * 添加前设置有效
 */
typedef NS_ENUM(NSInteger, QTextureLineDrawType) {
    QTextureLineDrawType_ColorLine = -1,        // 不使用纹理, 而且以颜色的形式绘制, 使用segmentColor中色值绘制
    QTextureLineDrawType_SliceAsBackground,     // 将图片以1像素为单位按行切片，根据下标从图片选取1像素来绘制线路样式(最大支持16像素高)
    QTextureLineDrawType_RepeatDraw,            // 重复绘制整个图片
    QTextureLineDrawType_FootPrint,             // 以足迹的形式重复绘制整个图片
};

/**
 * @brief 具有丰富显示样式的线覆盖物
 *
 * 默认在楼块之下(QOverlayLevelAboveRoads). 
 * 支持多种样式的分段显示
 */
@interface QTexturePolylineView : QPolylineView

/**
 * @brief 线绘制方式.
 *
 * 默认为QTextureLineDrawType_SliceAsBackground. 添加完成后不支持修改
 */
@property (nonatomic, assign) QTextureLineDrawType drawType;

#pragma mark 分段颜色线
/**
 * @brief 定义了各子线段的颜色. 当 QTextureLineDrawType_ColorLine 有效.
 *
 * 支持实时修改
 * 目前仅支持15种不同的颜色对
 */
@property (nonatomic, copy) NSArray<QSegmentColor *> *segmentColor;

#pragma mark 纹理线通用
/**
 * @breif 绘制线所采用的纹理. 当非QTextureLineDrawType_ColorLine有效.
 *
 * 可为nil. 为nil时则采用默认样式的纹理
 * 当QTextureLineDrawType_SliceAsBackground时, 要求图片为以1像素为单位的多行的图片.样例参照color_texture.png图片
 */
@property (nonatomic, strong) UIImage  *styleTextureImage;

#pragma mark 分段纹理线
/**
 * @brief 定义了各子线段的样式. 当 非QTextureLineDrawType_ColorLine 有效.
 *
 * 支持实时修改
 */
@property (nonatomic, copy) NSArray<QSegmentStyle *> *segmentStyle;

#pragma mark 纹理线上的箭头
/**
 * @brief 是否绘制箭头图标
 *
 * 当QTextureLineDrawType_SliceAsBackground和QTextureLineDrawType_ColorLine时有效
 */
@property (nonatomic, assign, getter=isDrawSymbol) BOOL   drawSymbol;

/**
 * @breif 箭头图标。默认采用默认样式箭头
 *
 * 当QTextureLineDrawType_SliceAsBackground和QTextureLineDrawType_ColorLine时有效
 */
@property (nonatomic, strong) UIImage  *symbolImage;

/**
 * @breif 箭头之间的间距. 单位：Point
 *
 * 当QTextureLineDrawType_SliceAsBackground和QTextureLineDrawType_ColorLine时有效
 */
@property (nonatomic, assign) CGFloat   symbolGap;


#pragma mark 路线擦除

/**
 * @breif 擦掉时时采用的颜色. 默认为灰色(置灰)
 *
 * 当QTextureLineDrawType_ColorLine时有效
 */
@property (nonatomic, strong) UIColor  *eraseColor;

/**
 * @brief 路线擦除功能，将从起点开始到coordinate坐标的路线颜色置灰或擦除
 *
 * @param coordinate 被擦除的终点坐标
 * @param pointIndex 终点所在子线段起点的下标
 * @param clearColor yes则擦除 no则置灰(参照eraseColor)
 *
 * 当QTextureLineDrawType_SliceAsBackground和QTextureLineDrawType_ColorLine时有效
 */
- (void)eraseFromStartToCurrentPoint:(CLLocationCoordinate2D)coordinate searchFrom:(int)pointIndex toColor:(BOOL)clearColor;

#pragma mark 脚印线
/**
 * @brief footprints之间的间距。 单位：Point
 *
 * 仅当TextureLineDrawType_FootPrint时有效
 */
@property (nonatomic, assign) CGFloat   footprintStep;

@end

/**
 * @brief 导航线相关的接口
 */
@interface QTexturePolylineView (Navigation)

/**
 * @brief 设置转向箭头的位置
 *
 * @note 箭头的显示级别为QOverlayLevelAboveBuilds
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

