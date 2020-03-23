//
//  TrafficPolyline.h
//  TNKNavigation
//
//  Created by fan on 2018/3/28.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QMapKit/QMapKit.h>

@interface TrafficPolyline : QPolyline

- (id)initWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count arrLine:(NSArray<QSegmentColor*> *)arrLine;

/** @brief 每一条路线的所有分段信息**/
@property(nonatomic, strong) NSMutableArray<QSegmentColor *>* arrLine;

@end
