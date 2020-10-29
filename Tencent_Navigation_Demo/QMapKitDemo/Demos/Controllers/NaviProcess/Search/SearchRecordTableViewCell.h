//
//  SearchRecordTableViewCell.h
//  TNKNavigationDebugging
//
//  Created by ikaros on 2020/4/27.
//  Copyright © 2020 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface SearchRecordTableViewCell : UITableViewCell

@property (nonatomic, strong) UILabel *labelText;

@property (nonatomic, strong) UIImageView *iconImageView;
@property (nonatomic, strong) UILabel *titleLabel;
@property (nonatomic, strong) UILabel *addressLabel;
@property (nonatomic, strong) UILabel *distanceLabel;

@end

NS_ASSUME_NONNULL_END
