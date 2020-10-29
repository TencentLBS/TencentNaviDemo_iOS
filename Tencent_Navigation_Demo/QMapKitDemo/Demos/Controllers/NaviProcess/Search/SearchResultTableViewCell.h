//
//  SearchResultTableViewCell.h
//  NavigationDemo
//
//  Created by xue on 2018/1/16.
//  Copyright © 2018年 xue. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SearchResultTableViewCell : UITableViewCell

@property (nonatomic, strong) UIImageView *iconImageView;
@property (nonatomic, strong) UILabel *titleLabel;
@property (nonatomic, strong) UILabel *addressLabel;
@property (nonatomic, strong) UILabel *distanceLabel;

@end
