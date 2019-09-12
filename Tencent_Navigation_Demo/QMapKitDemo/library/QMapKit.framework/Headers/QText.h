//
//  QText.h
//  QMapKit
//
//  Created by fan on 2019/8/9.
//  Copyright © 2019 tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CLLocation.h>

NS_ASSUME_NONNULL_BEGIN

/**
*  @brief 文本显示的优先级. 可用于在文本有碰撞时决定压盖关系. High显示在Normal上方.
*         默认为QTextPriority_High
*  @note  仅在文本信息间发生碰撞时，才需将低层级的文本信息priority设为QTextPriority_Normal
*/
typedef enum QRTextPriority {
    QTextPriority_Normal,       ///< 普通优先级
    QTextPriority_High          ///< 高优先级
} QTextPriority;

/**
*  @brief 文本信息的显示样式
*/
@interface QTextStyle : NSObject

/**
*  @brief 字的颜色
*/
@property (nonatomic, strong) UIColor    *textColor;

/**
*  @brief 字的描边色
*/
@property (nonatomic, strong) UIColor    *strokeColor;

/**
*  @brief 字的字号. 默认14
*/
@property (nonatomic, assign) CGFloat   fontSize;

/**
*  @brief 字的优先级。当多个文本间有碰撞时更高的优先显示. 默认为QTextPriority_High.
 *
 * @notes 期望显示在最顶部的文本请保证为QTextPriority_High
*/
@property (nonatomic, assign) QTextPriority    priority;
        
@end

/**
*  @brief 代表单段显示的文本内容
*/
@interface QSegmentText : NSObject

/**
*  @brief 本段在轨迹点串中的起始下标. 从0开始
*/
@property (nonatomic, assign) int startIndex;

/**
*  @brief 本段在轨迹点串中的终止下标. 请确保大于startIndex
*/
@property (nonatomic, assign) int endIndex;

/**
*  @brief 本段的文本内容
*/
@property (nonatomic, copy ) NSString *name;

@end


/**
*  @brief 此类用于显示文本信息, 层级与POI label相同
*  @notes 需保证最上层显示的文本信息中QTextStyle priority为QTextPriority_High
*         以及对应的overlayview的displayLevel为QOverlayLevelAboveRoads 或者
*         QOverlayLevelAboveBuildings。
*/
@interface QText : NSObject

/**
*  @brief 文本信息的显示样式
*/
@property (nonatomic, strong) QTextStyle   *style;

/**
*  @brief 文本信息的数据。可沿路径显示，可在每段(QSegmentText)显示不同的文本
*/
@property (nonatomic, readonly) NSArray<QSegmentText *> *segments;

/**
 *  @brief  根据子段的数据生成文本信息
 *
 *  @param segments 各子段的文本数据序列. 请确保各子段的范围无重叠
 *
 *  @return 生成的文本
 */
- (instancetype)initWithSegments:(NSArray<QSegmentText *> *)segments;

@end

NS_ASSUME_NONNULL_END
