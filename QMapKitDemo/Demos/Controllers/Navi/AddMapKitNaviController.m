//
//  AddMapKitNaviController.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/10.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "AddMapKitNaviController.h"

@interface AddMapKitNaviController()
@property(strong, nonatomic) QPolyline *polyline;
@property CLLocationCoordinate2D endPoi;
@property BOOL flag;
@end

@implementation AddMapKitNaviController

- (QOverlayView *)mapView:(QMapView *)mapView viewForOverlay:(id<QOverlay>)overlay
{
    if ([overlay isKindOfClass:[QPolyline class]])
    {
        QPolylineView *polylineView = [[QPolylineView alloc] initWithPolyline:overlay];
        polylineView.lineWidth   = 2;
        NSArray<NSNumber *> *lineDashPattern = [[NSArray alloc] initWithObjects:[[NSNumber alloc] initWithInt:20], [[NSNumber alloc] initWithInt:20], nil];
        polylineView.lineDashPattern = lineDashPattern;
        polylineView.strokeColor = [UIColor blackColor];
        
        return polylineView;
    }
    
    return nil;
}


- (void)mapView:(QMapView *)mapView didUpdateUserLocation:(QUserLocation *)userLocation fromHeading:(BOOL)fromHeading
{
    if(!self.flag)
    {
        [self startNavi:userLocation.location.coordinate];
        self.flag = YES;
    }
    if(self.polyline != nil) {
        [self.naviView.naviMapView removeOverlay:self.polyline];
    }
    CLLocationCoordinate2D lineCoord[2];
    lineCoord[0] = userLocation.location.coordinate;
    lineCoord[1] = self.endPoi;
    self.polyline = [QPolyline polylineWithCoordinates:lineCoord count:2];
    [self.naviView.naviMapView addOverlay:self.polyline];
}

- (void) startNavi:(CLLocationCoordinate2D)startPoi
{
    // get Information of navigation
    
    TNKSearchNaviPoi *start = [[TNKSearchNaviPoi alloc] init];
    start.coordinate = startPoi;
    
    TNKSearchNaviPoi *dest  = [[TNKSearchNaviPoi alloc] init];
    dest.coordinate = self.endPoi;
    
    TNKCarRouteSearchOption *option = [[TNKCarRouteSearchOption alloc] init];     option.avoidTrafficJam = YES;
    option.startRoadType = TNKRoadType_MainRoad;
    
    TNKCarRouteSearchRequest *request = [[TNKCarRouteSearchRequest alloc] init];
    request.startPoint = start;
    request.destinationPoint = dest;
    request.searchOption = option;
    
    [self.carManager searchNavigationRoutesWithRequest:request completion:^(TNKCarRouteSearchResult *result, NSError *error) {
        if(error == nil)
        {
            [self.carManager startWithIndex:0];
        }
    }];
}

-(void)viewDidLoad
{
    [super viewDidLoad];
    self.endPoi = CLLocationCoordinate2DMake(39.9930, 116.3376);
    [self.naviView.naviMapView setShowsUserLocation:YES];
}


@end
