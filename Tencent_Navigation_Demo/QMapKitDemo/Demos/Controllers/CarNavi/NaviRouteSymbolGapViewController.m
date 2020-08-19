//
//  NaviRouteSymbolGapViewController.m
//  QMapKitDemo
//
//  Created by ikaros on 2020/8/19.
//  Copyright © 2020 tencent. All rights reserved.
//

#import "NaviRouteSymbolGapViewController.h"

@interface NaviRouteSymbolGapViewController ()

@end

@implementation NaviRouteSymbolGapViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.naviView.routeSymbolGap = 10;
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
