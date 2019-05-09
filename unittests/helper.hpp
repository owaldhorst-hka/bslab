//
//  helper.hpp
//  testing
//
//  Created by Oliver Waldhorst on 15.12.17.
//  Copyright © 2017 Oliver Waldhorst. All rights reserved.
//

#ifndef helper_hpp
#define helper_hpp

#include "blockdevice.h"

void gen_random(char *s, const int len);
void bdWriteRead(BlockDevice *bd, int noBlocks= 1);

#endif /* helper_hpp */
