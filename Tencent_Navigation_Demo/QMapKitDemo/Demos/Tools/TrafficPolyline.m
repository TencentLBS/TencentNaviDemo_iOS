//
//  TrafficPolyline.m
//  TNKNavigation
//
//  Created by fan on 2018/3/28.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import "TrafficPolyline.h"

@implementation TrafficPolyline

- (id)initWithCoordinates:(CLLocationCoordinate2D *)coordinateArray count:(NSUInteger)count arrLine:(NSArray<QSegmentColor *> *)arrLine
{
    if (count == 0 || arrLine.count == 0) {
        return nil;
    }
    
    if (self = [super initWithCoordinates:coordinateArray count:count])
    {
        self.arrLine = [NSMutableArray array];
        [self.arrLine addObjectsFromArray:arrLine];
    }
    
    return self;
}

@end
