//
//  TrafficPolyline.m
//  TNKNavigation
//
//  Created by fan on 2018/3/28.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import "RoutePolyline.h"

@implementation RoutePolyline

- (id)initWithCoordinates:(CLLocationCoordinate2D *)coordinateArray count:(NSUInteger)count roadName:(QText *)texts
{
    if (count == 0) {
        return nil;
    }
    
    if (self = [super initWithCoordinates:coordinateArray count:count])
    {
        self.arrLine = [NSMutableArray array];
        self.texts   = texts;
    }
    
    return self;
}

- (id)initWithCoordinates:(CLLocationCoordinate2D *)coordinateArray count:(NSUInteger)count arrLine:(NSArray<QSegmentColor *> *)arrLine roadName:(QText *)texts
{
    if (count == 0 || arrLine.count == 0) {
        return nil;
    }
    
    if (self = [super initWithCoordinates:coordinateArray count:count])
    {
        self.arrLine = [NSMutableArray array];
        self.texts   = texts;
        [self.arrLine addObjectsFromArray:arrLine];
    }
    
    return self;
}

- (void)setSelectedLine:(BOOL)selectedLine {
    if (_selectedLine == selectedLine) {
        return;
    }
    _selectedLine = selectedLine;
    
    self.segments = self.segments;
}

- (void)setSegments:(NSArray<TNKRouteTrafficData *> *)segments {

    _segments = segments;
    
    NSMutableArray* routeLineArray = [NSMutableArray array];
    for (TNKRouteTrafficData *trafficData in segments) {
        QSegmentColor *subLine = [[QSegmentColor alloc] init];
        subLine.startIndex = (int)trafficData.from;
        subLine.endIndex   = (int)trafficData.to;

        subLine.color = _selectedLine ? TNKRouteTrafficStatusColor(trafficData.color) : TNKAccompanyRouteTrafficStatusColor(trafficData.color);
        subLine.borderColor = _selectedLine ? TNKRouteTrafficStatusBorderColor(trafficData.color) : TNKAccompanyRouteTrafficStatusBorderColor(trafficData.color);
        
        [routeLineArray addObject:subLine];
    }
    
    self.arrLine = routeLineArray;
}

@end
