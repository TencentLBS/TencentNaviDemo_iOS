//
//  NaviRouteColorViewController.m
//  QMapKitDemo
//
//  Created by ikaros on 2020/8/19.
//  Copyright © 2020 tencent. All rights reserved.
//

#import "NaviRouteColorViewController.h"

@interface NaviRouteColorViewController ()

@end

@implementation NaviRouteColorViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self setRouteColor];
}

- (void)setRouteColor {
       NSDictionary *routeColorDictionary = @{@(TNKRouteTrafficDataStatusSmooth):[UIColor cyanColor],@(TNKRouteTrafficDataStatusSlow):[UIColor blueColor],@(TNKRouteTrafficDataStatusVerySlow):[UIColor blackColor],@(TNKRouteTrafficDataStatusUnkown):[UIColor greenColor],@(TNKRouteTrafficDataStatusJam):[UIColor yellowColor]};
     self.naviView.routeColorDictionary = routeColorDictionary;
}
/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
