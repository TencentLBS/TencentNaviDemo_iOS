//
//  NaviSearchRoutes.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/7.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "NaviSearchRoutes.h"

@implementation NaviSearchRoutes

- (QAnnotationView *)mapView:(QMapView *)mapView viewForAnnotation:(id<QAnnotation>)annotation
{
    if ([annotation isKindOfClass:[QPointAnnotation class]])
    {
        static NSString *pointReuseIndetifier = @"pointReuseIndetifier";
        QPinAnnotationView *annotationView = (QPinAnnotationView*)[self.naviView.naviMapView dequeueReusableAnnotationViewWithIdentifier:pointReuseIndetifier];
        
        if (annotationView == nil)
        {
            annotationView = [[QPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:pointReuseIndetifier];
        }
        
        return annotationView;
    }
    
    return nil;
}

- (QOverlayView *)mapView:(QMapView *)mapView viewForOverlay:(id<QOverlay>)overlay
{
    if ([overlay isKindOfClass:[QCircle class]])
    {
        QCircleView *circleRender = [[QCircleView alloc] initWithCircle:overlay];
        
        circleRender.lineWidth   = 3;
        circleRender.strokeColor = [UIColor blueColor];
        circleRender.fillColor   = [UIColor colorWithRed:1 green:0 blue:0 alpha:.3];
        
        return circleRender;
    }
    else if ([overlay isKindOfClass:[QPolygon class]])
    {
        QPolygonView *polygonRender = [[QPolygonView alloc] initWithPolygon:overlay];
        polygonRender.lineWidth   = 3;
        polygonRender.strokeColor = [UIColor colorWithRed:.2 green:.1 blue:.1 alpha:.8];
        polygonRender.fillColor   = [[UIColor blueColor] colorWithAlphaComponent:0.2];
        
        return polygonRender;
    }
    else if ([overlay isKindOfClass:[QPolyline class]])
    {
        QPolylineView *polylineRender = [[QPolylineView alloc] initWithPolyline:overlay];
        polylineRender.lineWidth   = 5;
        polylineRender.strokeColor = [UIColor greenColor];
        
        return polylineRender;
    }
    
    return nil;
}

-(void)searchRoutes
{
    // get Information of navigation
    NSMutableArray<QPointAnnotation*> *annotations = [NSMutableArray array];
    
    TNKSearchNaviPoi *start = [[TNKSearchNaviPoi alloc] init];
    CLLocationCoordinate2D startPoi = {39.9842, 116.3074};
    start.coordinate = startPoi;
    
    TNKSearchNaviPoi *dest  = [[TNKSearchNaviPoi alloc] init];
    CLLocationCoordinate2D endPoi = {39.9930, 116.3376};
    dest.coordinate = endPoi;
    
    QPointAnnotation* annotation = [[QPointAnnotation alloc] init];
    annotation.coordinate = CLLocationCoordinate2DMake(39.9930, 116.3376);
    [annotations addObject:annotation];
    
    annotation = [[QPointAnnotation alloc] init];
    annotation.coordinate = CLLocationCoordinate2DMake(39.9842, 116.3074);
    [annotations addObject:annotation];
    
    
    //[self.naviView.naviMapView setCenterCoordinate:CLLocationCoordinate2DMake((startPoi.latitude + endPoi.latitude) / 2, (startPoi.longitude + endPoi.longitude) / 2)];
    //[self.naviView.naviMapView setZoomLevel:13.0f];
    
    TNKCarRouteSearchOption *option = [[TNKCarRouteSearchOption alloc] init];
    option.avoidTrafficJam = YES;
    option.startRoadType = TNKRoadType_MainRoad;
    option.avoidHighway = YES;
    
    TNKCarRouteSearchRequest *request = [[TNKCarRouteSearchRequest alloc] init];
    request.startPoint = start;
    request.destinationPoint = dest;
    request.searchOption = option;
    
    
    NSMutableArray<TNKSearchNaviPoi*> *wayPoints = [NSMutableArray array];
    [wayPoints addObject:[[TNKSearchNaviPoi alloc]init]];
    wayPoints[0].coordinate = CLLocationCoordinate2DMake(39.9841, 116.3163);
    [wayPoints addObject:[[TNKSearchNaviPoi alloc]init]];
    wayPoints[1].coordinate = CLLocationCoordinate2DMake(39.9894, 116.3271);
    request.wayPoints = wayPoints;
    
    annotation = [[QPointAnnotation alloc] init];
    annotation.coordinate = CLLocationCoordinate2DMake(39.9841, 116.3163);
    [annotations addObject:annotation];
    
    annotation = [[QPointAnnotation alloc] init];
    annotation.coordinate = CLLocationCoordinate2DMake(39.9894, 116.3271);
    [annotations addObject:annotation];
    
    
    
    [self.carManager searchNavigationRoutesWithRequest:request completion:^(TNKCarRouteSearchResult *result, NSError *error) {
        if(error == nil)
        {
            NSArray<TNKCoordinatePoint *> *route = result.routes[0].line.coordinatePoints;
            NSUInteger len = [route count];
            CLLocationCoordinate2D line[len];
            for(NSUInteger i = 0; i < len; i++)
            {
                line[i] = route[i].coordinate;
            }
            [self.naviView.naviMapView addOverlay:[[QPolyline alloc] initWithCoordinates:line count:len]];
            [annotations enumerateObjectsUsingBlock:^(QPointAnnotation * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
                [self.naviView.naviMapView addAnnotation:obj];
            }];
            //[self.naviView.naviMapView addOverlays:annotations];
        }
    }];
}

#pragma mark - Life Cycle
- (void)viewDidLoad
{
    [super viewDidLoad];
    [self searchRoutes];
}

@end
