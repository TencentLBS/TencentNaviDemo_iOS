//
//  MainViewController.m
//  TNKNavigation
//
//  Created by tabsong on 2018/3/28.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import "CarPlanController.h"
#import <QMapKit/QMapKit.h>
#import "RoutePolyline.h"
#import "NavigationViewController.h"
#import "SearchViewController.h"
#import "SVProgressHUD.h"
#import "MathTool.h"
#import "NaviPoi.h"
#import <AVFoundation/AVFoundation.h>
#import <TNKNavigationKit/TNKNavigationKit.h>
#import "EntryViewController.h"

#define RecommendPlanButtonTag 100

@interface CarPlanController ()
<TNKCarNaviDelegate,QMapViewDelegate,UIGestureRecognizerDelegate,
NavigationViewControllerDelegate, SearchViewControllerDelegate,
SearchViewControllerDataSource, TNKCarNaviUIDelegate,UITextFieldDelegate>

@property (nonatomic, strong) TNKCarNaviManager *carNaviManager;

@property (nonatomic, strong) UIView *topView;
@property (nonatomic, strong) UIView *toolBarView;
@property (nonatomic, strong) QMapView *mapView;
@property (nonatomic, strong) UILongPressGestureRecognizer *longPressGestureGecognizer;
@property (nonatomic, strong) QPointAnnotation *destAnnotation;

@property (nonatomic, strong) NSArray <RoutePolyline *> *routePolylines;

@property (nonatomic, strong) UIButton *locateButton;
@property (nonatomic, strong) UIButton *trafficButton;
@property (nonatomic, strong) UIButton *backButton;
@property (nonatomic, strong) UIButton *initialButton;
@property (nonatomic, strong) UIButton *startNavigationButton;
@property (nonatomic, strong) UIButton *simulateNavigationButton;
@property (nonatomic, strong) UIButton *firstRecommendPlanButton;
@property (nonatomic, strong) UIButton *secondRecommendPlanButton;
@property (nonatomic, strong) UIButton *thirdRecommendPlanButton;

@property (nonatomic, strong) AVAudioPlayer *voicePlayer;

@property (nonatomic, strong) UITextField* textFieldDestPosition;
@property (nonatomic, strong) UITextField* textFieldStartPosition;

@property (nonatomic) NaviPoi *from;
@property (nonatomic) NaviPoi *to;
@property (nonatomic, strong) NSMutableArray* fromMutableArray;
@property (nonatomic, strong) NSMutableArray* toMutableArray;
@property (nonatomic, strong) NSMutableArray<TNKCarRouteSearchRoutePlan *> *routes;

@property (nonatomic, strong) TNKCarRouteSearchResult *routeResult;

@property (nonatomic, assign) BOOL firstLocationReady;
@property (nonatomic, assign) NSInteger selectedRouteIndex;

@end

@implementation CarPlanController

#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self setupMapView];
    
    [self setupToolBarView];
    
    [self setupStartAndDestNavigationBar];
    
    self.fromMutableArray = [[NSMutableArray alloc] init];
    self.toMutableArray   = [[NSMutableArray alloc] init];
    
    [self setupWidgets];
    
    //    [self setupGestures];
    
    [self setupCarManager];
    
    [self setStartPoiWithMyLocation];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [self.navigationController setNavigationBarHidden:YES animated:animated];
    
}

#pragma mark - Setup

- (void)setupCarManager
{
    self.carNaviManager = [[TNKCarNaviManager alloc] init];
    
    self.carNaviManager.enableInternalTTS = YES;
    self.carNaviManager.multiRoutesEnabled = YES;
    [self.carNaviManager registerNaviDelegate:self];
    self.carNaviManager.simulationSpeed = 76;
}

- (void)setupMapView
{
    self.mapView = [[QMapView alloc] initWithFrame:self.view.bounds];
    self.mapView.delegate = self;
    self.mapView.showsUserLocation = YES;
    self.mapView.showsTraffic = NO;
    
    [self.view addSubview:self.mapView];
}

- (void)setupStartAndDestNavigationBar
{
    CGSize btnSize = CGSizeMake(40, 45);
    UIEdgeInsets marginInsets = UIEdgeInsetsMake(5, 0, 12, 18);
    
    // topView
    self.topView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, self.view.bounds.size.width, 80 + 5 + kStatusBarHeight)];
    [self.topView setBackgroundColor:[UIColor whiteColor]];
    [self.view addSubview:self.topView];
    
    // backBarView
    UIButton *backBarButton = [[UIButton alloc] init];
    [backBarButton setBackgroundImage:[UIImage imageNamed:@"search bar__back_Normal"] forState:UIControlStateNormal];
    CGRect frame = CGRectMake(0, (self.topView.bounds.size.height + kStatusBarHeight - btnSize.height) / 2, btnSize.width, btnSize.height);
    backBarButton.frame = frame;
    [backBarButton addTarget:self action:@selector(handleExit:) forControlEvents:UIControlEventTouchUpInside];
    [self.topView addSubview:backBarButton];
    
    
    // barBgView
    CGFloat barBgViewHeight = self.topView.bounds.size.height - marginInsets.top - marginInsets.bottom - kStatusBarHeight;
    CGFloat barBgViewWidth = self.topView.bounds.size.width - CGRectGetMaxX(backBarButton.frame) - marginInsets.right;
    UIView *barBgView = [[UIView alloc] initWithFrame:CGRectMake(CGRectGetMaxX(backBarButton.frame), marginInsets.top + kStatusBarHeight,
                                                                 barBgViewWidth, barBgViewHeight)];
    barBgView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    barBgView.backgroundColor =  [UIColor colorWithWhite:243.0 / 255.0 alpha:1];
    barBgView.layer.cornerRadius = 3;
    [self.topView addSubview:barBgView];
    
    
    CGFloat dotWidth = 6.0f;
    CGFloat labelLeft = 30.0;
    CGSize labelSize = CGSizeMake(barBgView.bounds.size.width - labelLeft, barBgViewHeight / 2.0);
    
    // startDotView
    UIView *startDotView = [[UIView alloc] initWithFrame:CGRectMake(10, (labelSize.height - dotWidth) / 2.0, dotWidth, dotWidth)];
    startDotView.backgroundColor = [UIColor colorWithRed:106.0 / 255.0 green:190.0 / 255.0 blue:171.0 / 255.0 alpha:1];
    startDotView.layer.cornerRadius = dotWidth /  2.0;
    [barBgView addSubview:startDotView];
    
    // endDotView
    UIView *endDotView = [[UIView alloc] initWithFrame:CGRectMake(10, labelSize.height + (labelSize.height - dotWidth) / 2.0, dotWidth, dotWidth)];
    endDotView.backgroundColor = [UIColor colorWithRed:234.0 / 255.0 green:96.0 / 255.0 blue:84.0 / 255.0 alpha:1];
    endDotView.layer.cornerRadius = dotWidth /  2.0;
    [barBgView addSubview:endDotView];
    
    // startField
    self.textFieldStartPosition = [[UITextField alloc]initWithFrame:CGRectMake(labelLeft, 0, labelSize.width, labelSize.height)];
    self.textFieldStartPosition.userInteractionEnabled = YES;
    self.textFieldStartPosition.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    self.textFieldStartPosition.text = @"我的位置";
    self.textFieldStartPosition.font = [UIFont systemFontOfSize:14];
    self.textFieldStartPosition.delegate = self;
    [self.textFieldStartPosition addTarget:self action:@selector(handleStartSearch:) forControlEvents:UIControlEventTouchDown];
    [barBgView addSubview:self.textFieldStartPosition];
    
    // lineView
    UIImageView *lineView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"bg_line"]];
    frame = CGRectMake(0, barBgView.bounds.size.height / 2, barBgView.bounds.size.width, lineView.bounds.size.height);
    lineView.frame = frame;
    [barBgView addSubview:lineView];
    
    // endField
    self.textFieldDestPosition = [[UITextField alloc] initWithFrame:CGRectMake(labelLeft, CGRectGetMaxY(self.textFieldStartPosition.frame),
                                                                               labelSize.width, labelSize.height)];
    self.textFieldDestPosition.userInteractionEnabled = YES;
    self.textFieldDestPosition.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    self.textFieldDestPosition.text = @"请搜索终点位置";
    self.textFieldDestPosition.font = [UIFont systemFontOfSize:14];
    [self.textFieldDestPosition addTarget:self action:@selector(handleDestSearch:) forControlEvents:UIControlEventTouchDown];
    
    [barBgView addSubview:self.textFieldDestPosition];
}

- (void)setupToolBarView
{
    CGSize btnSize = CGSizeMake(120, 40);
    UIEdgeInsets marginInsets = UIEdgeInsetsMake(5, 0, 5, 0);
    
    // toolBarView
    self.toolBarView = [[UIView alloc] initWithFrame:CGRectMake(0, self.view.bounds.size.height - 130 - kHomeIndicatorHeight, self.view.bounds.size.width, 130 + kHomeIndicatorHeight)];
    [self.toolBarView setBackgroundColor:[UIColor whiteColor]];
    self.toolBarView.hidden = YES;
    [self.view addSubview:self.toolBarView];
    
    // real start
    self.startNavigationButton = [[UIButton alloc] init];
    self.startNavigationButton.frame = CGRectMake(self.toolBarView.bounds.size.width / 5 - btnSize.width / 3,
                                                  CGRectGetMaxY(self.toolBarView.bounds) - btnSize.height - marginInsets.bottom - kHomeIndicatorHeight,
                                                  btnSize.width, btnSize.height);
    [self.startNavigationButton setTitle:@"开始导航" forState:UIControlStateNormal];
    [self.startNavigationButton setImage:[UIImage imageNamed:@"icon_route_press_Normal"] forState:UIControlStateNormal];
    self.startNavigationButton.titleLabel.font = [UIFont boldSystemFontOfSize:16];
    self.startNavigationButton.layer.cornerRadius = btnSize.height / 2.0;
    [self.startNavigationButton setTitleColor:[UIColor colorWithRed:56.0 / 255.0 green:143 / 255.0 blue:247.0 / 255.0 alpha:1]
                                     forState:UIControlStateNormal];
    self.startNavigationButton.backgroundColor = [UIColor whiteColor];
    self.startNavigationButton.layer.borderColor = [UIColor colorWithRed:56.0 / 255.0 green:143 / 255.0 blue:247.0 / 255.0 alpha:1].CGColor;
    self.startNavigationButton.layer.borderWidth = 1.0;
    [self.startNavigationButton addTarget:self action:@selector(handleStart:) forControlEvents:UIControlEventTouchDown];
    [self.toolBarView addSubview:self.startNavigationButton];
    
    // simulate start
    self.simulateNavigationButton = [[UIButton alloc] init];
    self.simulateNavigationButton.frame = CGRectMake(3 *self.toolBarView.bounds.size.width / 5,
                                                     CGRectGetMaxY(self.toolBarView.bounds) - btnSize.height - marginInsets.bottom - kHomeIndicatorHeight,
                                                     btnSize.width, btnSize.height);
    [self.simulateNavigationButton setTitle:@"模拟导航" forState:UIControlStateNormal];
    [self.simulateNavigationButton setImage:[UIImage imageNamed:@"ic_routelist_select_Normal"] forState:UIControlStateNormal];
    self.simulateNavigationButton.titleLabel.font = [UIFont boldSystemFontOfSize:16];
    self.simulateNavigationButton.layer.cornerRadius = btnSize.height / 2.0;
    self.simulateNavigationButton.backgroundColor = [UIColor colorWithRed:56.0 / 255.0 green:143 / 255.0 blue:247.0 / 255.0 alpha:1];
    [self.simulateNavigationButton addTarget:self action:@selector(handleSimulateStart:) forControlEvents:UIControlEventTouchDown];
    [self.toolBarView addSubview:self.simulateNavigationButton];
    
    // line
    UIImageView *lineView = [[UIImageView alloc] initWithFrame:CGRectMake(marginInsets.left,
                                                                          CGRectGetMaxY(self.toolBarView.bounds) - btnSize.height - marginInsets.bottom - 8 - kHomeIndicatorHeight,
                                                                          self.view.frame.size.width, 1)];
    UIImage *lineImage = [UIImage imageNamed:@"bg_line"];
    [lineView setImage:lineImage];
    [self.toolBarView addSubview:lineView];
    
    self.firstRecommendPlanButton = [[UIButton alloc] init];
    [self.toolBarView addSubview:self.firstRecommendPlanButton];
    self.firstRecommendPlanButton.tag = RecommendPlanButtonTag;
    [self.firstRecommendPlanButton addTarget:self action:@selector(handlePlanButtons:) forControlEvents:UIControlEventTouchDown];
    
    self.secondRecommendPlanButton = [[UIButton alloc] init];
    [self.toolBarView addSubview:self.secondRecommendPlanButton];
    self.secondRecommendPlanButton.tag = RecommendPlanButtonTag + 1;
    [self.secondRecommendPlanButton addTarget:self action:@selector(handlePlanButtons:) forControlEvents:UIControlEventTouchDown];
    
    self.thirdRecommendPlanButton = [[UIButton alloc] init];
    [self.toolBarView addSubview:self.thirdRecommendPlanButton];
    self.thirdRecommendPlanButton.tag = RecommendPlanButtonTag + 2;
    [self.thirdRecommendPlanButton addTarget:self action:@selector(handlePlanButtons:) forControlEvents:UIControlEventTouchDown];
}

- (void)setupWidgets
{
    CGFloat margin = 5;
    CGFloat width = self.view.frame.size.width;
    CGFloat height = self.view.frame.size.height;
    CGFloat trafficButtonSize = 50;
    
//    self.trafficButton = [UIButton buttonWithType:UIButtonTypeCustom];
//    self.trafficButton.frame = CGRectMake(width - margin - trafficButtonSize, self.topView.frame.origin.y + self.topView.frame.size.height + margin, trafficButtonSize, trafficButtonSize);
//    [self.trafficButton setBackgroundImage:[UIImage imageNamed:@"map_traffic_normal"] forState:UIControlStateNormal];
//
//    [self.trafficButton addTarget:self action:@selector(handleTraffic:) forControlEvents:UIControlEventTouchUpInside];
//
//    [self.view addSubview:self.trafficButton];
    

    
    self.backButton = [UIButton buttonWithType:UIButtonTypeCustom];
    self.backButton.frame = CGRectMake(width - margin - trafficButtonSize, self.trafficButton.frame.origin.y + self.topView.frame.origin.y + self.topView.frame.size.height + margin + margin, trafficButtonSize, trafficButtonSize);
    [self.backButton setBackgroundImage:[UIImage imageNamed:@"simulator_normal"] forState:UIControlStateNormal];
    self.backButton.hidden = YES;
    [self.backButton addTarget:self action:@selector(handleMenu:) forControlEvents:UIControlEventTouchUpInside];
    
    [self.view addSubview:self.backButton];
    
}


//- (void)setupGestures
//{
//    self.longPressGestureGecognizer = [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(handleLongPress:)];
//    self.longPressGestureGecognizer.delegate = self;
//    self.longPressGestureGecognizer.minimumPressDuration = 1;
//    [self.view addGestureRecognizer:self.longPressGestureGecognizer];
//}


//- (BOOL)textFieldShouldClear:(UITextField *)textField
//{
//    if (textField.text.length == 0) {
//        return NO;
//    }
//    return YES;
//}


- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField {
    NSLog(@"这里返回为NO。则为禁止编辑");
    return NO;
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string {
    if(textField == self.textFieldStartPosition){
        if (textField.text.length < 5 || string.length == 0){
            return YES;
        }
        else{
            return NO;
        }
    }
    return YES;
}




#pragma mark - QMapViewDelegate

- (QAnnotationView *)mapView:(QMapView *)mapView viewForAnnotation:(id<QAnnotation>)annotation
{
    if ([annotation isKindOfClass:[QPointAnnotation class]])
    {
        if ([annotation.title isEqualToString:@"destinationAnnotation"])
        {
            NSString *identifier = @"destination";
            QAnnotationView *annotationView = [self.mapView dequeueReusableAnnotationViewWithIdentifier:identifier];
            if (!annotationView)
            {
                annotationView = [[QAnnotationView alloc] init];
            }
            annotationView.image = [UIImage imageNamed:@"ic_end"];
            return annotationView;
        }
        else if ([annotation.title isEqualToString:@"startAnnotation"])
        {
            NSString *identifier = @"start";
            QAnnotationView *annotationView = [self.mapView dequeueReusableAnnotationViewWithIdentifier:identifier];
            if (!annotationView)
            {
                annotationView = [[QAnnotationView alloc] init];
            }
            annotationView.image = [UIImage imageNamed:@"ic_start"];
            return annotationView;
        }
        else
        {
            static NSString *pointReuseIndetifier = @"pointReuseIndetifier";
            QPinAnnotationView *annotationView = (QPinAnnotationView *)[self.mapView dequeueReusableAnnotationViewWithIdentifier:pointReuseIndetifier];
            
            if (annotationView == nil)
            {
                annotationView = [[QPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:pointReuseIndetifier];
            }
            
            annotationView.canShowCallout   = NO;
            annotationView.pinColor = QPinAnnotationColorRed;
            annotationView.animatesDrop = YES;
            
            return annotationView;
        }
    }
    
    return nil;
}

- (QOverlayView *)mapView:(QMapView *)mapView viewForOverlay:(id<QOverlay>)overlay
{
    if ([overlay isKindOfClass:[RoutePolyline class]])
    {
        RoutePolyline *tl = (RoutePolyline*)overlay;
        
        QTexturePolylineView *polylineRender = [[QTexturePolylineView alloc] initWithPolyline:overlay];
        polylineRender.drawType     = QTextureLineDrawType_ColorLine;
        polylineRender.drawSymbol = YES;
        polylineRender.segmentColor = tl.arrLine;
        polylineRender.lineWidth   = 10;
        polylineRender.borderWidth = 1.5;
        polylineRender.text    = tl.texts;
        polylineRender.zIndex = tl.selectedLine?1:0;
        return polylineRender;
    }
    else if ([overlay isKindOfClass:[QPolyline class]])
    {
        QPolylineView *polylineRender = [[QPolylineView alloc] initWithPolyline:overlay];
        polylineRender.borderColor = [UIColor colorWithRed:0 green:0.8 blue:0 alpha:0.15];
        polylineRender.lineWidth   = 10;
        polylineRender.borderWidth = 1;
        polylineRender.strokeColor = [UIColor colorWithRed:1 green:0 blue:0 alpha:.248];
        return polylineRender;
    }else if ([overlay isKindOfClass:[QPolygon class]]) {
        QPolygonView *polygonView = [[QPolygonView alloc] initWithPolygon:overlay];
        polygonView.lineWidth = 2;
        polygonView.strokeColor = [UIColor grayColor];
        polygonView.fillColor = [UIColor clearColor];
        
        return polygonView;
    }
    
    return nil;
}

- (void)mapView:(QMapView *)mapView didTapOverlay:(id<QOverlay>)overlay
{
    NSInteger index = [self.routePolylines indexOfObject:overlay];
    [self changeRoute:index];
    [self configRecommendPlanButtonsWithSelectedIndex:index];
}

- (void)mapView:(QMapView *)mapView didUpdateUserLocation:(QUserLocation *)userLocation fromHeading:(BOOL)fromHeading
{
    if(self.firstLocationReady == NO && userLocation.location != nil)
    {
        [self setStartPoiWithMyLocation];
        self.firstLocationReady = YES;
        [self setCenterCoordinate:userLocation.location.coordinate];
    }
}

#pragma mark - TNKCarNaviDelegate

- (int)carNavigationManager:(TNKCarNaviManager *)manager broadcastTTS:(TNKNaviTTS *)naviTTS
{
    //    NSLog(@"%s tts = %@ voice type = %d", __FUNCTION__, naviTTS.ttsString, naviTTS.voiceType);
    //
    //    if(naviTTS.voiceType == TNKNaviTTSVoiceTypeBeep)
    //    {
    //        NSError *error;
    //
    //        self.voicePlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:[NSURL URLWithString:naviTTS.voiceFilePath] error:&error];
    //        self.voicePlayer.volume = 1.0;
    //
    //        if(error == nil)
    //        {
    //            [self.voicePlayer play];
    //        }
    //
    //        __weak __typeof(self)weakSelf = self;
    //
    //        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
    //            [weakSelf speechWithVal:naviTTS.ttsString];
    //        });
    //    }
    //    else
    //    {
    //        [self speechWithVal:naviTTS.ttsString];
    //    }
    return 1;
}

- (void)carNavigationManagerDidArriveDestination:(TNKCarNaviManager *)manager
{
    NSLog(@"%s", __FUNCTION__);
    
    //[self speechWithVal:@"您已到达终点附近，导航结束"];
}

- (void)carNavigationManagerDidOffRoute:(TNKCarNaviManager *)manager
{
    NSLog(@"%s", __FUNCTION__);
    
    //[self speechWithVal:@"已经偏航"];
}

- (void)carNavigationManager:(TNKCarNaviManager *)manager
   didSuccessRecaculateRoute:(TNKCarNaviManagerRecaculateType)type
                      result:(TNKCarRouteSearchResult *)result
{
    NSLog(@"%s", __FUNCTION__);
}

- (void)carNavigationManager:(TNKCarNaviManager *)manager
      didFailRecaculateRoute:(TNKCarNaviManagerRecaculateType)type
                       error:(NSError *)error
{
    NSLog(@"%s", __FUNCTION__);
}

#pragma mark - NaviStatus Manager.


- (NSMutableArray <TNKCarRouteSearchRoutePlan *> *)planItemsForNaviResult:(TNKCarRouteSearchResult *)result
{
    if (result.routes.count == 0)
    {
        NSLog(@"route.count = 0");
        return nil;
    }
    self.routes = [NSMutableArray arrayWithArray:result.routes];
    
    return self.routes;
}

- (RoutePolyline *)polylineForNaviResult:(TNKCarRouteSearchRoutePlan *)plan isSelected:(BOOL)isSelected {
    TNKCarRouteSearchRouteLine *line = plan.line;
    
    NSArray <TNKRouteTrafficData *> *segments = line.initialTrafficDataArray;
    int count = (int)line.coordinatePoints.count;
    CLLocationCoordinate2D *coordinateArray = (CLLocationCoordinate2D*)malloc(sizeof(CLLocationCoordinate2D)*count);
    for (int i = 0; i < count; ++i) {
        coordinateArray[i] = [(TNKCoordinatePoint*)[line.coordinatePoints objectAtIndex:i] coordinate];
    }

    NSMutableArray<QSegmentText *> *segmentTexts = [NSMutableArray array];
    for (int i = 0; i < line.segmentItems.count; i++)  {
        TNKSegmentItem *segmentItem = line.segmentItems[i];
        
        QSegmentText *segmentText = [[QSegmentText alloc] init];
        segmentText.startIndex = segmentItem.currentIndexStart;
        segmentText.endIndex   = segmentItem.nextIndexStart;
        segmentText.name       = segmentItem.roadName;
        [segmentTexts addObject:segmentText];
    }

    
    QTextStyle *style = [[QTextStyle alloc] init];
    style.textColor = [UIColor blackColor];
    style.strokeColor = [UIColor whiteColor];
    style.fontSize = 18;
    
    QText *texts = [[QText alloc] initWithSegments:segmentTexts];
    texts.style = style;
    
    // 创建路线,一条路线由一个点数组和线段数组组成
    RoutePolyline *routeOverlay = [[RoutePolyline alloc] initWithCoordinates:coordinateArray count:count roadName:texts];
    routeOverlay.segments = segments;
    routeOverlay.selectedLine = isSelected;
    
    free(coordinateArray);
    
    return routeOverlay;
}

- (NSArray <RoutePolyline *> *)polylineForNaviResult:(TNKCarRouteSearchResult *)result
{
    if (result.routes.count == 0)
    {
        NSLog(@"route.count = 0");
        return nil;
    }
    
    NSArray <TNKCarRouteSearchRoutePlan *> *plans =  result.routes;
    
    NSMutableArray <TNKCarRouteSearchRouteLine *> *lines = [[NSMutableArray alloc] init];
    
    NSMutableArray <RoutePolyline *> *routeOverlays = [[NSMutableArray alloc] init];
    
    for (int i = 0; i < plans.count; i++)
    {
        [lines addObject:plans[i].line];
    }
    
    for (TNKCarRouteSearchRouteLine *line in lines)
    {
        NSArray<TNKRouteTrafficData *> *segments = line.initialTrafficDataArray;
        int count = (int)line.coordinatePoints.count;
        CLLocationCoordinate2D *coordinateArray = (CLLocationCoordinate2D*)malloc(sizeof(CLLocationCoordinate2D)*count);
        for (int i = 0; i < count; ++i)
        {
            coordinateArray[i] = [(TNKCoordinatePoint*)[line.coordinatePoints objectAtIndex:i] coordinate];
        }
        
        
        NSMutableArray* routeColorArray = [NSMutableArray array];
        
        for (TNKRouteTrafficData *seg in segments)
        {
            
            QSegmentColor *segColorLine = [[QSegmentColor alloc] init];
            segColorLine.startIndex = (int)seg.from;
            segColorLine.endIndex   = (int)seg.to;
            
            if (line == [lines objectAtIndex:self.selectedRouteIndex])
            {
                segColorLine.color       = TNKRouteTrafficStatusColor(seg.color);
                segColorLine.borderColor = TNKRouteTrafficStatusBorderColor(seg.color);
            }
            else
            {
                segColorLine.color       = TNKAccompanyRouteTrafficStatusColor(seg.color);
                segColorLine.borderColor = TNKAccompanyRouteTrafficStatusBorderColor(seg.color);
            }
            [routeColorArray addObject:segColorLine];
            
        }
        
        NSMutableArray<QSegmentText *> *segmentTexts = [NSMutableArray array];
        for (int i = 0; i < line.segmentItems.count; i++)
        {
            TNKSegmentItem *segmentItem = line.segmentItems[i];
            
            if (segmentItem.segRoadNames.count == 0) {
                QSegmentText *segmentText = [[QSegmentText alloc] init];
                segmentText.startIndex = segmentItem.currentIndexStart;
                segmentText.endIndex   = segmentItem.nextIndexStart;
                segmentText.name       = segmentItem.roadName;
                [segmentTexts addObject:segmentText];
            }else {
                for (int j = 0; j < segmentItem.segRoadNames.count; j++) {
                    QSegmentText *segmentText = [[QSegmentText alloc] init];
                    segmentText.startIndex = segmentItem.segRoadNames[j].from;
                    segmentText.endIndex   = segmentItem.segRoadNames[j].to;
                    segmentText.name       = segmentItem.segRoadNames[j].roadName;
                    [segmentTexts addObject:segmentText];
                }
            }
        }

        
        QTextStyle *style = [[QTextStyle alloc] init];
        style.textColor = [UIColor blackColor];
        style.strokeColor = [UIColor whiteColor];
        style.fontSize = 18;
        
        QText *texts = [[QText alloc] initWithSegments:segmentTexts];
        texts.style = style;
        
        RoutePolyline *routeOverlay = [[RoutePolyline alloc] initWithCoordinates:coordinateArray count:count arrLine:routeColorArray roadName:texts];
        
        [routeOverlays addObject:routeOverlay];
        free(coordinateArray);
    }
    
    return [routeOverlays copy];
}

- (QMapRect)visibleMapRectForNaviResult:(TNKCarRouteSearchResult *)result
{
    NSAssert(result.routes.count != 0, @"route count 0 error");
    
    TNKCarRouteSearchRoutePlan *plan = result.routes[self.selectedRouteIndex];
    TNKCarRouteSearchRouteLine *line = plan.line;
    
    return [MathTool mapRectFitsPoints:line.coordinatePoints];
}

- (void)searchFrom:(NaviPoi *)from to:(NaviPoi *)to {
    
    NSArray<NSArray<NSArray<NSNumber *> *> *> *avoidAreaList = [self avoidAreaCase1];
    NSMutableArray<NSArray<TNKCoordinatePoint *> *> *avoidAreaArray = [NSMutableArray array];
    
    for (NSArray<NSArray<NSNumber *> *> *avoidArea in avoidAreaList) {
    
        CLLocationCoordinate2D coordinates[avoidArea.count];
        NSMutableArray<TNKCoordinatePoint *> *coordinatePoints = [NSMutableArray array];
        
        for (int i = 0; i < avoidArea.count; i++) {
            NSArray<NSNumber *> * point = avoidArea[i];
            coordinates[i].latitude = [point[0] doubleValue];
            coordinates[i].longitude = [point[1] doubleValue];
            
            TNKCoordinatePoint *coordinatePoint = [[TNKCoordinatePoint alloc] init];
            coordinatePoint.coordinate = coordinates[i];
            [coordinatePoints addObject:coordinatePoint];
        }
        
        [avoidAreaArray addObject:coordinatePoints];
        QPolygon *polygon = [QPolygon polygonWithCoordinates:coordinates count:avoidArea.count];
        [self.mapView addOverlay:polygon];
    }
    
    
//    QPointAnnotation *point1 = [[QPointAnnotation alloc] init];
//    point1.coordinate = CLLocationCoordinate2DMake(39.966727, 116.307278);
//    QPointAnnotation *point2 = [[QPointAnnotation alloc] init];
//    point2.coordinate = CLLocationCoordinate2DMake(39.968832, 116.437569);
//    QPointAnnotation *point3 = [[QPointAnnotation alloc] init];
//    point3.coordinate = CLLocationCoordinate2DMake(39.862317, 116.454391);
//    QPointAnnotation *point4 = [[QPointAnnotation alloc] init];
//    point4.coordinate = CLLocationCoordinate2DMake(39.853093, 116.314487);
//
//    [self.mapView addAnnotation:point1];
//    [self.mapView addAnnotation:point2];
//    [self.mapView addAnnotation:point3];
//    [self.mapView addAnnotation:point4];
    
    TNKSearchNaviPoi *start = [[TNKSearchNaviPoi alloc] init];
    start.coordinate = from.coordinate;
    start.uid = from.uid;
    
//    start.coordinate = CLLocationCoordinate2DMake(40.037748, 116.477114);
//    start.uid = nil;
    
    //start.coordinate = CLLocationCoordinate2DMake(39.994199,116.379993);  // 惯导
    //start.coordinate = CLLocationCoordinate2DMake(40.028637,116.300020);  // 封路
    //start.coordinate = CLLocationCoordinate2DMake(39.994161,116.380615);  // 在对面
    //start.coordinate = CLLocationCoordinate2DMake(40.166703,116.172172);  // 围栏
    //start.coordinate = CLLocationCoordinate2DMake(39.975143,116.302831);  // 4K
    //start.coordinate = CLLocationCoordinate2DMake(39.984975,116.307412);  // 终点
    //start.coordinate = CLLocationCoordinate2DMake(39.983707,116.30821);   // 性能
    //start.coordinate = CLLocationCoordinate2DMake(39.974697,116.301672);  // 擦除
    
    TNKSearchNaviPoi *dest = [[TNKSearchNaviPoi alloc] init];
    dest.coordinate = to.coordinate;
    dest.uid = to.uid;
//    dest.coordinate = CLLocationCoordinate2DMake(40.10804, 116.56208);
//    dest.uid = nil;
    
    //dest.coordinate = CLLocationCoordinate2DMake(39.995033,116.412622);   // 惯导
    //dest.coordinate = CLLocationCoordinate2DMake(40.026727,116.300647);   // 封路
    //dest.coordinate = CLLocationCoordinate2DMake(39.994815,116.404738);   // 在对面
    //dest.coordinate = CLLocationCoordinate2DMake(40.166621,116.178754);   // 围栏
    //dest.coordinate = CLLocationCoordinate2DMake(39.978140,116.302643);   // 4K
    //dest.coordinate = CLLocationCoordinate2DMake(39.982558,116.308109);   // 终点
    //dest.coordinate = CLLocationCoordinate2DMake(39.896835,116.319423);   // 性能
    //dest.coordinate = CLLocationCoordinate2DMake(39.896835,116.319423);   // 擦除
    
    TNKCarRouteSearchOption *option = [[TNKCarRouteSearchOption alloc] init];
    option.avoidTrafficJam = YES;
    
    //车牌限号 周一38 周二49 周三50 周四16 周五27
    //option.carNumber = @"京P12343";
    
    TNKCarRouteSearchRequest *request = [[TNKCarRouteSearchRequest alloc] init];
    request.startPoint = start;
    request.destinationPoint = dest;
    request.searchOption = option;
    request.routeSearchRetryTimes = 5;
    [request setAvoidAreas:avoidAreaArray];
    
    //    NSMutableArray<TNKSearchNaviPoi*> *wayPoints = [NSMutableArray array];
    //    [wayPoints addObject:[[TNKSearchNaviPoi alloc]init]];
    //    wayPoints[0].coordinate = CLLocationCoordinate2DMake(23.113834, 113.322473);
    //    [wayPoints addObject:[[TNKSearchNaviPoi alloc]init]];
    //
    ////    wayPoints[0].coordinate = CLLocationCoordinate2DMake(23.113794, 113.325107);
    ////    [wayPoints addObject:[[TNKSearchNaviPoi alloc]init]];
    //    wayPoints[1].coordinate = CLLocationCoordinate2DMake(23.115146, 113.324597);
    //    request.wayPoints = wayPoints;
    
    [SVProgressHUD showWithStatus:@"规划路线中.."];
    [SVProgressHUD setDefaultMaskType:SVProgressHUDMaskTypeClear];
    
    __weak CarPlanController *weakSelf = self;
    
    [self.carNaviManager searchNavigationRoutesWithRequest:request completion:^(TNKCarRouteSearchResult *result, NSError *error) {
        
        __strong CarPlanController *strongSelf = weakSelf;
        
        if (!strongSelf) {
            return;
        }
        
        if(error)
        {
            [SVProgressHUD showErrorWithStatus:error.description];
            [SVProgressHUD dismissWithDelay:1.0f];
            
        }
        else
        {
            NSLog(@"naviRoutes Data is Ready. count: %lu", (unsigned long)result.routes.count);
            
            dispatch_async(dispatch_get_main_queue(), ^{
                
                [self removeOverlayAndAnnotationview];
                
                int selectedIndex = 0;
                strongSelf.selectedRouteIndex = 0;
                strongSelf.routes = [result.routes mutableCopy];
                
                NSMutableArray *tmpArray = [NSMutableArray arrayWithCapacity:result.routes.count];
                for (int i = 0; i < result.routes.count; i++) {
                    TNKCarRouteSearchRoutePlan *routePlan = result.routes[i];
                    RoutePolyline *polyline = [strongSelf polylineForNaviResult:routePlan isSelected:i == selectedIndex];
                    [strongSelf.mapView addOverlay:polyline];
                    [tmpArray addObject:polyline];
                }
                
                // 路线.
                strongSelf.routeResult = result;
                strongSelf.routePolylines = [tmpArray copy]; // [strongSelf polylineForNaviResult:result];
                strongSelf.routes = [strongSelf planItemsForNaviResult:result];
                
                //设置RecommendPlanButton
                if (strongSelf.routes.count > 0)
                {
                    [strongSelf updateRecommendPlanButtonsFrame];
                    [strongSelf updateRecommendPlanButtonsAttributedTitle];
                    [strongSelf configRecommendPlanButtonsWithSelectedIndex:0];
                    
                    [strongSelf addOverlayAndAnnotationview];
                    [strongSelf modifyRoutesRect];
                }
                strongSelf.toolBarView.hidden = NO;
                strongSelf.backButton.hidden = NO;
                strongSelf.initialButton.hidden = NO;
                [SVProgressHUD dismiss];
                
                
            });
        }
    }];
}

#pragma mark - NavigationViewControllerDelegate

- (void)navigationViewControllerDidStop:(NavigationViewController *)navigationViewController
{

}

- (void)setIndoorEnabled:(BOOL)indoorEnabled
{
    indoorEnabled = YES;
}

- (CLLocation *)searchViewControllerStartLocationForSearchRequest:(SearchViewController *)searchViewController
{
    return self.mapView.userLocation.location;
}


#pragma mark - SearchViewControllerDelegate

// 获取data并且分配给from搜索框和to搜索框
- (void)searchViewController:(SearchViewController *)searchViewController didSuccessSearchWithData:(QMSSuggestionPoiData *)data
{
    
    if (searchViewController.pointSearchType == PointSearchType_Start)
    {
        //设置起点
        [self setStartPoiWithSuggestionPoiData:data];
        
        if ([self.textFieldDestPosition.text isEqualToString: @"我的位置"])
        {
            [self setDestinationPoiWithMyLocation];
        }
    }
    
    if (searchViewController.pointSearchType == PointSearchType_Destination)
    {
        //设置终点
        [self setDestinationPoiWithSuggestionPoiData:data];
        
        if ([self.textFieldStartPosition.text isEqualToString:@"我的位置"])
        {
            [self setStartPoiWithMyLocation];
        }
    }
    
    //开始搜索
    [self beginSearchRoute];
    
}

- (void)searchViewController:(SearchViewController *)searchViewController didFailSearchWithError:(NSError *)error
{
    
}

- (void)searchViewControllerDidSelectedMyLocation:(SearchViewController *)searchViewController
{
    if (searchViewController.pointSearchType == PointSearchType_Start)
    {
        [self setStartPoiWithMyLocation];
    }
    
    if (searchViewController.pointSearchType == PointSearchType_Destination)
    {
        [self setDestinationPoiWithMyLocation];
    }
    
    [self beginSearchRoute];
}

#pragma mark - Private

/**
 设置起点
 */
- (void)setStartPoiWithSuggestionPoiData:(QMSSuggestionPoiData *)data
{
    
    self.from.coordinate = data.location;
    self.from.uid = data.id_;
    
    if (data.title.length != 0)
    {
        self.textFieldStartPosition.text = data.title;
    }
    
    [self.fromMutableArray addObject:data];
    
    if ([self.toMutableArray count] != 0)
    {
        
        if ([self.fromMutableArray count] > 1)
        {
            [self.fromMutableArray removeObjectAtIndex:0];
        }
        
        QMSSuggestionPoiData *toData = self.toMutableArray[self.toMutableArray.count - 1];
        self.to.coordinate           = toData.location;
        self.to.uid                  = toData.id_;
        
        //        [self addDestAnnotation:toData.location];
    }
}


/**
 设置终点
 */
- (void)setDestinationPoiWithSuggestionPoiData:(QMSSuggestionPoiData *)data
{
    if (!self.to)
    {
        self.to = [[NaviPoi alloc] init];
    }
    
    self.to.coordinate = data.location;
    self.to.uid = data.id_;
    
    if (data.title.length != 0)
    {
        self.textFieldDestPosition.text = data.title;
    }
    
    [self.toMutableArray addObject: data];
    
    if ([self.fromMutableArray count] != 0)
    {
        
        if ([self.toMutableArray count] > 1)
        {
            [self.toMutableArray removeObjectAtIndex:0];
        }
        
        QMSSuggestionPoiData *fromData = self.fromMutableArray[self.fromMutableArray.count - 1];
        self.from.coordinate = fromData.location;
        self.from.uid = nil;
    }
}

/**
 *  设置起点为“我的位置”
 */
- (void)setStartPoiWithMyLocation
{
    self.textFieldStartPosition.text = @"我的位置";
    self.from.coordinate = self.mapView.userLocation.location.coordinate;
    self.from.uid = nil;
}

/**
 * 设置终点为“我的位置”
 */
- (void)setDestinationPoiWithMyLocation
{
    self.textFieldDestPosition.text = @"我的位置";
    self.to.coordinate = self.mapView.userLocation.location.coordinate;
    self.to.uid = nil;
}

/**
 * 开始搜索路线
 */
- (void)beginSearchRoute
{
    if (self.from && self.to)
    {
        self.selectedRouteIndex = 0;
        [self searchFrom:self.from to:self.to];
    }
    else
    {
        return;
    }
}

/**
 * 移除大头针和路线
 */
- (void)removeOverlayAndAnnotationview
{
    [self.mapView removeOverlays:self.routePolylines];
    [self.mapView removeAnnotation:self.destAnnotation];
}

/**
 * 添加大头针和路线
 */
- (void)addOverlayAndAnnotationview
{
    //添加终点
    self.destAnnotation.coordinate = self.to.coordinate;
    self.destAnnotation.title = @"destinationAnnotation";
    [self.mapView addAnnotation:self.destAnnotation];
    
    //添加路线
    [self.mapView addOverlays: [self arrayResort:self.routePolylines]];
}

// 数组选中的元素放到最后一个，其余元素依次向前移动
- (NSArray<RoutePolyline *> *)arrayResort: (NSArray <RoutePolyline *> *)array
{
    NSMutableArray *mutableArray = [array mutableCopy];
    RoutePolyline *object = [mutableArray objectAtIndex:self.selectedRouteIndex];
    [mutableArray removeObjectAtIndex:self.selectedRouteIndex];
    [mutableArray addObject:object];
    
    return [mutableArray copy];
}


- (void)changeRoute:(NSInteger) selectedIndex {
    
    if (self.selectedRouteIndex == selectedIndex) {
        return;
    }
    
    RoutePolyline *preSelectedLine = self.routePolylines[self.selectedRouteIndex];
    
    self.selectedRouteIndex = selectedIndex;
    
    RoutePolyline *selectedLine = self.routePolylines[selectedIndex];
    
    QTexturePolylineView *selectedLineView = (QTexturePolylineView *)[self.mapView viewForOverlay:selectedLine];
    QTexturePolylineView *preSelectedLineView = (QTexturePolylineView *) [self.mapView viewForOverlay:preSelectedLine];
    
    selectedLine.selectedLine = YES;
    preSelectedLine.selectedLine = NO;
    
    selectedLineView.segmentColor = selectedLine.arrLine;
    preSelectedLineView.segmentColor = preSelectedLine.arrLine;
    
    selectedLineView.zIndex = 1;
    preSelectedLineView.zIndex = 0;
    
    [self modifyRoutesRect];
    
}

- (void)modifyRoutesRect {
    QMapRect mapRect = [self visibleMapRectForNaviResult:self.routeResult];
    [self.mapView setVisibleMapRect:mapRect edgePadding:UIEdgeInsetsMake(kNavigationBarHeight + 64 + 15, 30, kHomeIndicatorHeight + 64 + 100 + 15, 30) animated:YES];
}
#pragma mark - RecommendPlanButtons

- (void)updateRecommendPlanButtonsFrame
{
    NSInteger count = self.routes.count;
    
    float margin = 10;
    float button_width = (self.toolBarView.frame.size.width - (count-1)*margin)/count;
    float button_height = 80;
    
    for (int i = 0; i < 3; i++)
    {
        UIButton *button = [self.toolBarView viewWithTag:i+RecommendPlanButtonTag];
        button.titleLabel.numberOfLines = 0;
        button.titleLabel.textAlignment = NSTextAlignmentCenter;
        
        if (i >= self.routes.count)
        {
            button.hidden = YES;
        }
        else
        {
            button.hidden = NO;
            button.frame = CGRectMake(i*margin + i*button_width, 0, button_width, button_height);
        }
    }
}

- (void)updateRecommendPlanButtonsAttributedTitle
{
    for (int index = 0 ; index < self.routes.count; index++)
    {
        NSMutableAttributedString *attributedString = [self recommendPlanButtonsAttributedTitleWithIndex:index isSelected:NO];
        NSMutableAttributedString *selectedAttributedString = [self recommendPlanButtonsAttributedTitleWithIndex:index isSelected:YES];
        
        UIButton *button = [self.toolBarView viewWithTag:index + RecommendPlanButtonTag];
        [button setAttributedTitle:attributedString forState:UIControlStateNormal];
        [button setAttributedTitle:selectedAttributedString forState:UIControlStateSelected];
    }
}

- (NSMutableAttributedString *)recommendPlanButtonsAttributedTitleWithIndex:(NSInteger)index isSelected:(BOOL)isSelected
{
    NSMutableAttributedString *attributedString = [[NSMutableAttributedString alloc] init];
    
    NSDictionary *smallFontAttr = @{NSFontAttributeName:[UIFont systemFontOfSize:12]};
    NSDictionary *largeFontAttr = @{NSFontAttributeName:[UIFont boldSystemFontOfSize:18]};
    
    NSAttributedString *recommendReason = [[NSAttributedString alloc] initWithString:[self.routes objectAtIndex:index].recommendReason attributes:smallFontAttr];
    [attributedString appendAttributedString:recommendReason];
    
    NSAttributedString *totalTime = [[NSAttributedString alloc] init];
    if ([self.routes objectAtIndex:index].totalTime < 60)
    {
        totalTime = [[NSAttributedString alloc] initWithString:[NSString stringWithFormat:@"\n%ld 分钟", (long)[self.routes objectAtIndex:index].totalTime] attributes:largeFontAttr];
    }
    else
    {
        totalTime = [[NSAttributedString alloc] initWithString:[NSString stringWithFormat:@"\n %i小时%i分钟", [self.routes objectAtIndex:index].totalTime / 60, [self.routes objectAtIndex:index].totalTime % 60] attributes:largeFontAttr];
    }
    [attributedString appendAttributedString:totalTime];
    
    NSAttributedString *totalDistance =  [[NSAttributedString alloc] initWithString: [NSString stringWithFormat:@"\n%.1f 公里", (long)[self.routes objectAtIndex:index].totalDistance/ 1000.00] attributes:smallFontAttr];
    [attributedString appendAttributedString:totalDistance];
    
    UIImage *img = [[UIImage alloc] init];
    if (isSelected)
    {
        img = [UIImage imageNamed:@"route_ic_trafficlight_hl"];
    }
    else
    {
        img = [UIImage imageNamed:@"route_ic_trafficlight"];
    }
    
    NSTextAttachment *textAttachment = [[NSTextAttachment alloc] init];
    textAttachment.image = img;
    NSAttributedString *attrStringWithImage = [NSAttributedString attributedStringWithAttachment:textAttachment];
    [attributedString appendAttributedString:attrStringWithImage];
    
    NSAttributedString *trafficLightNumber      = [[NSAttributedString alloc] initWithString: [NSString stringWithFormat:@"%i"  ,[self.routes objectAtIndex:index].trafficLightNumber] attributes:smallFontAttr];
    [attributedString appendAttributedString:trafficLightNumber];
    
    if ([self.routes objectAtIndex:index].fee != 0)
    {
        UIImage *feeImg = [[UIImage alloc] init];
        if (isSelected)
        {
            feeImg = [UIImage imageNamed:@"route_ic_cost_hl"];
        }
        else
        {
            feeImg = [UIImage imageNamed:@"route_ic_cost"];
        }
        
        NSTextAttachment *feeTextAttachment = [[NSTextAttachment alloc] init];
        feeTextAttachment.image = feeImg;
        NSAttributedString *attrStringWithImageFee = [NSAttributedString attributedStringWithAttachment:feeTextAttachment];
        [attributedString appendAttributedString:attrStringWithImageFee];
        
        NSAttributedString *fee = [[NSAttributedString alloc] initWithString: [NSString stringWithFormat:@"%li",(long)[self.routes objectAtIndex:index].fee] attributes:smallFontAttr];
        [attributedString appendAttributedString:fee];
    }
    
    if (isSelected)
    {
        UIColor *blueColor = [UIColor colorWithRed:70/255.0 green:128/255.0  blue:251/255.0 alpha:1];
        [attributedString addAttribute:NSForegroundColorAttributeName value:blueColor range:NSMakeRange(0, attributedString.length)];
    }
    else
    {
        [attributedString addAttribute:NSForegroundColorAttributeName value:[UIColor blackColor] range:NSMakeRange(0, attributedString.length)];
    }
    
    return attributedString;
}

- (void)configRecommendPlanButtonsWithSelectedIndex:(NSInteger)selectedIndex
{
    //设置选中状态
    for (int i = 0; i < self.routes.count; i++)
    {
        UIButton *button = [self.toolBarView viewWithTag:(i + RecommendPlanButtonTag)];
        if (button.tag == selectedIndex + RecommendPlanButtonTag)
        {
            button.selected = YES;
        }
        else
        {
            button.selected = NO;
        }
    }
}

#pragma mark - Actions

- (void)openNavigationControllerWithRouteIndex:(NSUInteger)routeIndex simulation:(BOOL)simulation
{
    NavigationViewController *controller = [[NavigationViewController alloc] initWithCarNaviManager:self.carNaviManager routeIndex:routeIndex simulateLocation:simulation];
    controller.delegate = self;
    
    [self.navigationController pushViewController:controller animated:YES];
}

- (void)handleStart:(UIBarButtonItem *)sender
{
    NSLog(@"%s", __FUNCTION__);
    
    //    [self.carManager startWithIndex:0];
    
    [self openNavigationControllerWithRouteIndex:self.selectedRouteIndex simulation:NO];
}

- (void)handleSimulateStart:(UIBarButtonItem *)sender
{
    NSLog(@"%s", __FUNCTION__);
    
    //    [self.carManager startSimulateWithIndex:0];
    
    
    [self openNavigationControllerWithRouteIndex:self.selectedRouteIndex simulation:YES];
}

- (void)handlePlanButtons:(UIButton *)button
{
    NSInteger index = button.tag - RecommendPlanButtonTag;
    [self configRecommendPlanButtonsWithSelectedIndex:index];
    
    [self changeRoute:index];

}

- (void)handleLongPress:(UILongPressGestureRecognizer *)gesture
{
    if (gesture.state != UIGestureRecognizerStateBegan)
    {
        return;
    }

    
    NSLog(@"%s", __FUNCTION__);
    
    CGPoint location  = [gesture locationInView:self.mapView];
    CLLocationCoordinate2D coordinate = [self.mapView convertPoint:location toCoordinateFromView:self.mapView];
    
    //    [self addDestAnnotation:coordinate];
    
    //    NaviPoi *from = [[NaviPoi alloc] init];
    //    from.coordinate = self.mapView.userLocation.location.coordinate;
    //
    //    NaviPoi *to = [[NaviPoi alloc] init];
    //    to.coordinate = self.destAnnotation.coordinate;
    
    
    NSString* fromString = self.textFieldStartPosition.text;
    
    self.from = [[NaviPoi alloc] init];
    self.to = [[NaviPoi alloc] init];
    
    if ([fromString isEqualToString:@"我的位置"])
    {
        self.from.coordinate = self.mapView.userLocation.location.coordinate;
    }
    else
    {
        QMSSuggestionPoiData *fromData = self.fromMutableArray[self.fromMutableArray.count - 1];
        self.from.coordinate = fromData.location;
        self.from.uid = nil;
    }
    
    self.to.coordinate = self.destAnnotation.coordinate;
    self.to.uid = nil;
    
    self.textFieldDestPosition.text = @"";
    
    [self searchFrom:self.from to:self.to];
    
}

//- (void)addDestAnnotation:(CLLocationCoordinate2D)coordinate
//{
//    [self.mapView removeAnnotation:self.destAnnotation];
//    [self.mapView removeOverlays:self.trafficLine];
//
//    self.destAnnotation = [[QPointAnnotation alloc] init];
//    self.destAnnotation.coordinate = coordinate;
//
//    [self.mapView addAnnotation:self.destAnnotation];
//}

- (void)handleDestSearch:(UIButton *)sender
{
    
    SearchViewController *search = [[SearchViewController alloc] init];
    
    search.delegate = self;
    search.dataSource = self;
    search.pointSearchType = PointSearchType_Destination;
    
    search.placeholderString = nil;
    [self.navigationController pushViewController:search animated:YES];
}

- (void)handleStartSearch:(UIButton *)sender
{
    
    SearchViewController *search = [[SearchViewController alloc] init];
    
    search.delegate = self;
    search.dataSource = self;
    search.pointSearchType = PointSearchType_Start;
    
    search.placeholderString = nil;
    
    
    [self.navigationController pushViewController:search animated:YES];
}

- (void)handleLocate:(UIButton *)sender
{
    if(self.mapView.userLocation.location != nil)
    {
        [self setCenterCoordinate:self.mapView.userLocation.location.coordinate];
    }
}
- (void)handleTraffic:(UIButton *)sender
{
    BOOL traffic = !self.mapView.showsTraffic;
    
    if(traffic)
    {
        [self.trafficButton setBackgroundImage:[UIImage imageNamed:@"map_traffic_active_normal"] forState:UIControlStateNormal];
    }
    else
    {
        [self.trafficButton setBackgroundImage:[UIImage imageNamed:@"map_traffic_normal"] forState:UIControlStateNormal];
    }
    
    self.mapView.showsTraffic = traffic;
}

- (void)handleMenu:(UIButton *)sender
{
    if(self.mapView.userLocation.location != nil)
    {
        [self removeOverlayAndAnnotationview];
        self.toolBarView.hidden = YES;
        self.textFieldDestPosition.text = nil;
        [self setCenterCoordinate:self.mapView.userLocation.location.coordinate];
    }
}

- (void)handleExit:(UIButton *)sender {
    
    [self removeOverlayAndAnnotationview];
    
    EntryViewController *mainVC = [[EntryViewController alloc] init];

    [self.navigationController popViewControllerAnimated:YES];
    [mainVC.navigationItem setHidesBackButton:YES];
    
}

- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate
{
    [self.mapView setCenterCoordinate:coordinate animated:YES];
}



#pragma mark - Lazy Load
- (NaviPoi *)from
{
    if (!_from)
    {
        _from = [[NaviPoi alloc] init];
        _from.coordinate = CLLocationCoordinate2DMake(self.mapView.userLocation.location.coordinate.latitude,
                                                      self.mapView.userLocation.location.coordinate.longitude);
    }
    return _from;
}

-(QPointAnnotation *)destAnnotation
{
    if (!_destAnnotation)
    {
        _destAnnotation = [[QPointAnnotation alloc] init];
    }
    return _destAnnotation;
}

// 北京二环
- (NSArray<NSArray<NSArray<NSNumber *> *> *> *)avoidAreaCase0 {
    
    NSArray<NSArray<NSArray<NSNumber *> *> *> *avoidAreaList= @[
        @[
            @[
                @(39.966727), @(116.318278),
            ],
            @[
                @(39.968832), @(116.447569),
            ],
            @[
                @(39.863317), @(116.454391),
            ],
            @[
                @(39.855093), @(116.324487),
            ],
        ],
    ];
    
    return avoidAreaList;
}

- (NSArray<NSArray<NSArray<NSNumber *> *> *> *)avoidAreaCase1 {
    
    // 终点，望京小街
    NSArray<NSArray<NSArray<NSNumber *> *> *> *avoidAreaList= @[
        @[
            @[
                @(39.989085), @(116.480833),
            ],
            @[
                @(39.988498), @(116.481755),
            ],
            @[
                @(39.987511), @(116.483252),
            ],
            @[
                @(39.987574), @(116.483381),
            ],
            @[
                @(39.987635), @(116.483329),
            ],
            @[
                @(39.988859), @(116.481467),
            ],
            @[
                @(39.989201), @(116.480933),
            ],
            @[
                @(39.989223), @(116.480885),
            ],
        ],
    ];
    
    return avoidAreaList;
}

- (NSArray<NSArray<NSArray<NSNumber *> *> *> *)avoidAreaCase2 {
    
    NSString *dataString = @"116.48342,39.987431;116.482027,39.986089;116.482027,39.986089;116.481363,39.985499;116.481675,39.985341;116.483703,39.987182\n\
    116.481359,39.985495;116.481489,39.985404;116.482513,39.984718;116.482678,39.984601;116.482726,39.98447;116.482549,39.984457;116.481240,39.985304\n\
    116.4825,39.984258;116.457773,39.961853;116.454583,39.959744;116.45444,39.959644;116.45418,39.959444;116.458082,39.958504;116.484175,39.982513\n\
    116.454175,39.95944;116.453576,39.958902;116.452908,39.958303;116.45263,39.958056;116.452932,39.957912;116.454418,39.959224\n\
    116.452626,39.958051;116.450677,39.956285;116.450334,39.955994;116.450347,39.955469;116.451613,39.954557;116.455293,39.956070\n\
    116.449987,39.95569;116.446467,39.952878;116.445217,39.951992;116.444748,39.95168;116.442354,39.954293;116.446109,39.957221\n\
    116.444744,39.951675;116.444774,39.951563;116.445277,39.952085;116.444966,39.952130;116.444762,39.951925\n\
    116.444774,39.951558;116.444141,39.951128;116.437344,39.944891;116.436689,39.945411;116.443985,39.951744\n\
    116.437339,39.944887;116.436532,39.944887;116.436532,39.944887;116.434006,39.944865;116.433948,39.944687;116.437322,39.944679\n\
    116.434002,39.944865;116.434002,39.944835;116.434023,39.94349;116.433958,39.94171;116.43398,39.941124;116.433138,39.941174;116.433063,39.944720\n\
    116.43398,39.94112;116.43401,39.940495;116.43401,39.940495;116.434262,39.935877;116.430466,39.936132;116.430509,39.941643\n\
    116.434262,39.935872;116.434314,39.93306;116.434362,39.932214;116.436818,39.932364;116.437011,39.935737\n\
    116.434362,39.932209;116.434544,39.932209;116.434768,39.932191;116.434785,39.931656;116.434361,39.931566\n\
    116.434544,39.932209;116.434544,39.93207;116.434753,39.923867;116.431217,39.922392;116.430659,39.932051\n\
    116.434826,39.922279;116.434852,39.92201;116.435117,39.915799;116.435126,39.915668;116.441388,39.915661;116.441646,39.922606\n\
    116.434826,39.922279;116.434852,39.92201;116.435126,39.915668;116.425767,39.915859;116.425703,39.922228\n\
    116.434447,39.915456;116.434436,39.915945;116.435326,39.915945;116.435135,39.915417";
    
    NSArray *lines = [dataString componentsSeparatedByString:@"\n"];
    NSMutableArray *avoidAreaList = [NSMutableArray array];

    for (NSString *line in lines) {
        
        NSArray *coords = [line componentsSeparatedByString:@";"];
        NSMutableArray *avoidArea = [NSMutableArray array];
        
        for (NSString *coordStr in coords) {
            
            NSArray *lnglatStr = [coordStr componentsSeparatedByString:@","];
            NSArray *latlng = @[@([lnglatStr[1] doubleValue]), @([lnglatStr[0] doubleValue])];
            [avoidArea addObject:latlng];
        }
        
        [avoidAreaList addObject:avoidArea];
        
    }
    
    return avoidAreaList;
}




@end

