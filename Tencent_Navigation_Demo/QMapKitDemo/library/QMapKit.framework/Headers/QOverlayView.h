//
//  QOverlayView.h
//  QMapKit
//
//  Created by fan on 2017/5/17.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "QOverlay.h"

/**
 *  @brief  该类是地图覆盖物View的基类, 提供了绘制overlay的接口, 但是没有实际实现。希望不要直接实例化
 */
@interface QOverlayView : UIView

@property (nonatomic, readonly) id <QOverlay> overlay;

@end
