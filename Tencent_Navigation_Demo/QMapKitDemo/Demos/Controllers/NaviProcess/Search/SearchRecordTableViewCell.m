//
//  SearchRecordTableViewCell.m
//  TNKNavigationDebugging
//
//  Created by ikaros on 2020/4/27.
//  Copyright © 2020 Tencent. All rights reserved.
//

#import "SearchRecordTableViewCell.h"

@implementation SearchRecordTableViewCell


-(instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        CGFloat width=[UIScreen mainScreen].bounds.size.width;
        CGFloat height=70;
        
        CGFloat margin=15;
        CGFloat iconSize=20;
        
        CGFloat distanceLabelWidth=90;
        CGFloat distanceLabelHeight=height/3;
        
        CGFloat titleLabelHeight=height/2+10;
        CGFloat addressLabelHeight=height/2-10;
        
        _iconImageView = [[UIImageView alloc]initWithFrame:CGRectMake(margin,(height-iconSize)/2, iconSize,iconSize)];
        [self.contentView addSubview:_iconImageView];
        
        _distanceLabel = [[UILabel alloc]initWithFrame:CGRectMake(width-distanceLabelWidth-margin, (height-distanceLabelHeight)/2, distanceLabelWidth,distanceLabelHeight)];
        _distanceLabel.textAlignment=NSTextAlignmentRight;
        _distanceLabel.font=[_distanceLabel.font fontWithSize:14];
        [self.contentView addSubview:_distanceLabel];
        
        _titleLabel = [[UILabel alloc]initWithFrame:CGRectMake(CGRectGetMaxX(_iconImageView.frame)+margin, 0, width-CGRectGetMaxX(_iconImageView.frame)-_distanceLabel.frame.size.width- 3*margin, titleLabelHeight)];
        _titleLabel.font=[_titleLabel.font fontWithSize:18];
        [self.contentView addSubview:_titleLabel];
        
        _addressLabel = [[UILabel alloc]initWithFrame:CGRectMake(CGRectGetMaxX(_iconImageView.frame)+margin, CGRectGetMaxY(_titleLabel.frame)-6, _titleLabel.frame.size.width, addressLabelHeight)];
        _addressLabel.font=[_addressLabel.font fontWithSize:14];
        _addressLabel.textColor=[UIColor lightGrayColor];
        [self.contentView addSubview:_addressLabel];
    }
    return self;
}
- (void)awakeFromNib {
    // Initialization code
    [super awakeFromNib];
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];
    
    // Configure the view for the selected state
}


@end
