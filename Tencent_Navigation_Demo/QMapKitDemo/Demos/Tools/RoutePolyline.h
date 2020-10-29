//
//  TrafficPolyline.h
//  TNKNavigation
//
//  Created by fan on 2018/3/28.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QMapKit/QMapKit.h>
#import <TNKNavigationKit/TNKNavigationKit.h>

@interface RoutePolyline : QPolyline

- (id)initWithCoordinates:(CLLocationCoordinate2D *)coordinateArray count:(NSUInteger)count roadName:(QText *)texts;
- (id)initWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count arrLine:(NSArray<QSegmentColor*> *)arrLine roadName:(QText *) texts;

/** @brief 每一条路线的所有分段信息**/
@property (nonatomic, strong) NSMutableArray<QSegmentColor *>* arrLine;

@property (nonatomic, strong) QText *texts;

@property (nonatomic, assign) BOOL selectedLine;

@property (nonatomic, copy) NSArray <TNKRouteTrafficData *> *segments;
@end
