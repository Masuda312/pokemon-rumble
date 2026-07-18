#include <BModelObj.hpp>

BModelObj::BModelObj(u32 group) : BWorldObj(group | 0x20), BSoundSource() {
    m_unknownStruct.m_field112_0x64 = &m_unknownStruct;
    m_unknownStruct.m_field112_0x68 = &m_unknownStruct;
    m_field112_0x6C = 0;
    m_updateFlag = 0;
    m_model = 0;
    m_field112_0x78 = 0;
    m_collisionScale.x = 1.f;
    m_collisionScale.y = 1.f;
    m_collisionScale.z = 1.f;
    m_hitBoxScale.x = 0.f;
    m_hitBoxScale.y = 0.f;
    m_hitBoxScale.z = 0.f;
    m_hitBoxPos.x = 0.f;
    m_hitBoxPos.y = 0.f;
    m_hitBoxPos.z = 0.f;
    m_field112_0xE8 = 1;
    m_field112_0xEC = 0;
    m_field112_0xF0 = 0;
    m_field112_0xF4 = &m_field112_0xF0;
}

nw4r::math::VEC3 BModelObj::getHitboxScale() {
    return m_hitBoxScale;
}

u32* BModelObj::get0xEC() {
    return &m_field112_0xEC;
}

// placed here because its a vfunc from BWorldObj in the range of BModelObj?
void BWorldObj::vfunc_80057CC0() {}

void BWorldObj::vfunc_80057CD0() {}

u32 BWorldObj::vfunc_80057CE0() {return 0;}

u32 BWorldObj::vfunc_80057CF0() {return 0;}

//void BModelObj::vfunc_80057A60() {
//    if (m_model) {
//        if ((m_objectActiveFlag & 1) == 0) {
//            if ((m_updateFlag & 2) == 0) {
//                m_updateFlag = m_updateFlag | 2;
//                fn_801C8310(m_model->m_scnMdl, 0);
//            }
//        } else if ((m_updateFlag & 2) != 0) {
//            m_updateFlag = m_updateFlag & 0xfffffffd;
//            fn_801C8310(m_model->m_scnMdl, 1);
//        }
//    }
//    if ((m_objectActiveFlag & 1) != 0) {
//        if ((m_updateFlag & 1) != 0) {
//            if (m_model) {
//                m_updateFlag = m_updateFlag & 0xfffffffe;
//                if ((m_updateFlag & 4) == 0) {
//          SinCosFIdx((double)((param_1->worldObj).angle * 0.7111111),&local_148,&local_144);
//          local_120 = -local_148;
//          local_80 = local_144;
//          local_7c = 0;
//          local_78 = local_148;
//          local_74 = 0;
//          local_70 = 0;
//          local_6c = 0x3f800000;
//          local_68 = 0;
//          local_64 = 0;
//          local_5c = 0;
//          local_58 = local_144;
//          local_54 = 0;
//          local_140 = local_144;
//          local_13c = 0;
//          local_138 = local_148;
//          local_134 = 0;
//          local_130 = 0;
//          local_12c = 0x3f800000;
//          local_128 = 0;
//          local_124 = 0;
//          local_11c = 0;
//          local_118 = local_144;
//          local_114 = 0;
//          local_e8 = (param_1->worldObj).scale.z;
//          local_110[5] = (param_1->worldObj).scale.y;
//          local_110[0] = (param_1->worldObj).scale.x;
//          local_110[1] = 0.0;
//          local_110[2] = 0.0;
//          local_110[3] = 0.0;
//          local_110[4] = 0.0;
//          local_f8 = 0;
//          local_f4 = 0;
//          local_f0 = 0;
//          local_ec = 0;
//          local_e4 = 0;
//          local_b4 = (param_1->worldObj).position.z;
//          local_c4 = (param_1->worldObj).position.y;
//          local_d4 = (param_1->worldObj).position.x;
//          local_e0 = 0x3f800000;
//          local_dc = 0;
//          local_d8 = 0;
//          local_d0 = 0;
//          local_cc = 0x3f800000;
//          local_c8 = 0;
//          local_c0 = 0;
//          local_bc = 0;
//          local_b8 = 0x3f800000;
//          local_60 = local_120;
//          __KMPLS_mult_dir(&local_e0,local_110,auStack_b0);
//          __KMPLS_mult_dir(auStack_b0,&local_140,auStack_50);
//          SetMtx(*(undefined4 *)(param_1->m_model + 8),0,auStack_50);
//        }
//        else {
//          SetMtx(*(undefined4 *)(param_1->m_model + 8),0,&param_1->field_0xb8);
//        }
//      }
//    }
//  }
//}

nw4r::math::VEC3 BWorldObj::getPosition() {
    return m_position;
}

void BModelObj::setAngle(f32 angle) {
    m_angle = angle;
    m_updateFlag = m_updateFlag | 1;
}
