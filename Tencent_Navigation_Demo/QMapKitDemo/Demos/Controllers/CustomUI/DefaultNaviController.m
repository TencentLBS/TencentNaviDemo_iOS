//
//  DefaultNaviController.m
//  QMapKitDemo
//
//  Created by Yuchen Wang on 2019/12/27.
//  Copyright © 2019 tencent. All rights reserved.
//

#import "DefaultNaviController.h"

@interface DefaultNaviController ()

@end

@implementation DefaultNaviController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.naviView.delegate = self;
    self.naviView.showUIElements = YES;
    
}

-(void)dealloc
{
    [self stopNavi];
}


#pragma mark - TNKCarNaviViewDelegate


- (void)carNaviViewCloseButtonClicked:(TNKCarNaviView *)carNaviView  {
    [self stopNavi];
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)stopNavi
{
    [self.carManager unregisterUIDelegate:self.naviView];
    
    [self.carManager stop];
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
