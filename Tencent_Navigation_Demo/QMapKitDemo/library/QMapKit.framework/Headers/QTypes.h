//
//  QTypes.h
//  QMapKit
//
//  Created by fan on 2017/6/24.
//  Copyright © 2017年 tencent. All rights reserved.
//

#ifndef QTypes_h
#define QTypes_h


/**
 *  @brief  底图内容的类型. 默认为QMapTypeStandard
 */
typedef NS_ENUM(NSUInteger, QMapType) {
    QMapTypeStandard = 0,       ///<标准地图
    QMapTypeSatellite           ///<卫星地图
};


typedef NS_ENUM (int, QMapStyleType) {
    QMapStyle_Normal            = 0,    // normal
    QMapStyle_Navigation        = 1,    // navigation
    QMapStyle_NavigationNight   = 2     // dark
} DEPRECATED_ATTRIBUTE;

/** @enum QMapLanguage 底图的语言
 * @brief 底图文字标注的首选语言
 */
typedef NS_ENUM(NSUInteger, QMapLanguage) {
    QMapLanguage_zh = 0,    ///< 中文
    QMapLanguage_en         ///< 英语
};


/**
 * @brief 覆盖物的显示级别，决定了与POI等地理元素的压盖关系
 */
typedef NS_ENUM(NSInteger, QOverlayLevel) {
    QOverlayLevelAboveRoads = 0,    // 在道路之上楼块之下
    QOverlayLevelAboveBuildings,    // 在楼块之上POI之下
    QOverlayLevelAboveLabels        // 显示在所有POI之上
};

/**
 * @brief 限制区域显示的限制方式，分别以区域宽度为参考值和以区域高度为参考值
 */
typedef NS_ENUM(NSInteger,QMapLimitRectFitMode) {
    QMapLimitRectFitWidth = 0,  // 此模式会以 mapRect宽度为参考值限制地图的控制区域，保证横向区域完全展示
    QMapLimitRectFitHeight      // 此模式会以 mapRect高度为参考值限制地图的控制区域，保证纵向区域完全展示
};

#endif /* QTypes_h */
