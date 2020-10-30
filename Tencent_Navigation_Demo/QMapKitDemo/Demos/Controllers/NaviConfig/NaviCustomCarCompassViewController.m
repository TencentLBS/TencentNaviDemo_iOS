//
//  NaviCustomCarCompassViewController.m
//  QMapKitDemo
//
//  Created by ikaros on 2020/10/30.
//  Copyright © 2020 tencent. All rights reserved.
//

#import "NaviCustomCarCompassViewController.h"

@interface NaviCustomCarCompassViewController ()

@end

@implementation NaviCustomCarCompassViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    TNKUserLocationPresentation *userLocationPresentation = [[TNKUserLocationPresentation alloc] init];
    userLocationPresentation.carIcon = [UIImage imageNamed:@"taxi"];
    userLocationPresentation.carIconWeak = [UIImage imageNamed:@"location"];
    userLocationPresentation.compassIcon = [UIImage imageNamed:@"compass"];
    [self.naviView configUserLocationPresentation:userLocationPresentation];
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
