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

#endif /* QTypes_h */
