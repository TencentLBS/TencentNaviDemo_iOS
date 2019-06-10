//
//  SimuNaviController.h
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/7.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "BaseNaviViewController.h"

@interface SimuNaviController: BaseNaviViewController
@property (strong)NSMutableArray<TNKSearchNaviPoi*> *wayPoints;
-(void)startNavi;
@end
