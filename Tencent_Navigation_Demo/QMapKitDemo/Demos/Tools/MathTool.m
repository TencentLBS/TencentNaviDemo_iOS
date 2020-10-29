//
//  MathTool.m
//  TNKNavigationDebugging
//
//  Created by ikaros on 2020/9/21.
//  Copyright © 2020 Tencent. All rights reserved.
//


#import "MathTool.h"

@implementation MathTool

/** @brief 计算地图适合的正方形点 **/
+ (QMapRect)mapRectFitsPoints:(NSArray<TNKCoordinatePoint *>*)points
{
    NSAssert(points != nil && points.count > 0, @"points array invalid");
    
    QMapPoint firstMapPoint = QMapPointForCoordinate(points[0].coordinate);
    
    CGFloat minX = firstMapPoint.x;
    CGFloat minY = firstMapPoint.y;
    CGFloat maxX = minX;
    CGFloat maxY = minY;
    
    for (int i = 1; i < points.count; i++) {
        
        QMapPoint point = QMapPointForCoordinate(points[i].coordinate);
        
        if (point.x < minX)
        {
            minX = point.x;
        }
        if (point.y < minY)
        {
            minY = point.y;
        }
        if (point.x > maxX)
        {
            maxX = point.x;
        }
        if (point.y > maxY)
        {
            maxY = point.y;
        }
        
    }
    
    CGFloat width  = fabs(maxX - minX);
    CGFloat height = fabs(maxY - minY);
    
    return QMapRectMake(minX, minY, width, height);
    
}

@end
