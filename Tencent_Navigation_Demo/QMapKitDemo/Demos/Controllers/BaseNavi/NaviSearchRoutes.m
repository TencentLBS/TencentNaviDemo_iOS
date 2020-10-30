//
//  NaviSearchRoutes.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/7.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "NaviSearchRoutes.h"
#import "TrafficPolyline.h"

@interface NaviSearchRoutes()

@property (nonatomic, strong) TrafficPolyline *trafficLine;

@end

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
//    else if ([overlay isKindOfClass:[QPolyline class]])
//    {
//        QPolylineView *polylineRender = [[QPolylineView alloc] initWithPolyline:overlay];
//        polylineRender.lineWidth   = 5;
//        polylineRender.strokeColor = [UIColor greenColor];
//
//        return polylineRender;
//    }
    else if([overlay isKindOfClass:[TrafficPolyline class]])
    {
        TrafficPolyline *tl = (TrafficPolyline*)overlay;
        QTexturePolylineView *polylineRender = [[QTexturePolylineView alloc] initWithPolyline:overlay];
        polylineRender.drawType = QTextureLineDrawType_ColorLine;
        polylineRender.drawSymbol = YES;
        polylineRender.segmentColor = tl.arrLine;
        polylineRender.lineWidth   = 10;
        polylineRender.borderWidth = 1.5;
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
    
     __weak typeof (self) weakSelf = self;
    
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
            
            weakSelf.trafficLine = [weakSelf polylineForNaviResult:result];
            [weakSelf.naviView.naviMapView addOverlay: weakSelf.trafficLine];
            [annotations enumerateObjectsUsingBlock:^(QPointAnnotation * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
                [weakSelf.naviView.naviMapView addAnnotation:obj];
            }];
            //[self.naviView.naviMapView addOverlays:annotations];
        }
    }];
}

- (TrafficPolyline *)polylineForNaviResult:(TNKCarRouteSearchResult *)result
{
    if (result.routes.count == 0)
    {
        NSLog(@"route.count = 0");
        return nil;
    }
    TNKCarRouteSearchRoutePlan *plan = result.routes[0];
    TNKCarRouteSearchRouteLine *line = plan.line;
    

    
//    for (int i = 0; i < line.wayPoints.count; i++) {
//        NSLog(@"wayPoints uid: %@", line.wayPoints[i].uid);
//        NSLog(@"wayPoints index: %d", line.wayPoints[i].wayPointIndex);
//    }
    
    NSArray <TNKRouteTrafficData *> *segments = line.initialTrafficDataArray;
    int count = (int)line.coordinatePoints.count;
    CLLocationCoordinate2D *coordinateArray = (CLLocationCoordinate2D*)malloc(sizeof(CLLocationCoordinate2D)*count);
    for (int i = 0; i < count; ++i)
    {
        coordinateArray[i] = [(TNKCoordinatePoint*)[line.coordinatePoints objectAtIndex:i] coordinate];
    }
    
    NSMutableArray* routeLineArray = [NSMutableArray array];
    for (TNKRouteTrafficData *trafficData in segments) {
        QSegmentColor *subLine = [[QSegmentColor alloc] init];
        subLine.startIndex = (int)trafficData.from;
        subLine.endIndex   = (int)trafficData.to;
        subLine.color = TNKRouteTrafficStatusColor(trafficData.color);
        subLine.borderColor = TNKRouteTrafficStatusBorderColor(trafficData.color);
        [routeLineArray addObject:subLine];
    }
    
    // 创建路线,一条路线由一个点数组和线段数组组成
    TrafficPolyline *routeOverlay = [[TrafficPolyline alloc] initWithCoordinates:coordinateArray count:count arrLine:routeLineArray];
    
    free(coordinateArray);
    
    return routeOverlay;
}

#pragma mark - Life Cycle
- (void)viewDidLoad
{
    [super viewDidLoad];
    [self searchRoutes];
}

@end
