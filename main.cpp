#include <pthread.h>
#include <jni.h>
#include <memory.h>
#include <dlfcn.h>
#include <cstdio>
#include <cstdlib>

#include "Includes/Logger.h"
#include "Patching/Patch.h"
#include "Includes/Utils.h"

bool UnlimitedAmmoCrossbow = false;
bool UnlimitedAmmoElectricGun = false;
bool UnlimitedAmmoFireGun = false;
bool UnlimitedAmmoLaserGun = false;
bool UnlimitedAmmoSniper = false;
bool UnlimitedAmmoWeapon = false;
bool UnlimitedAmmoMultiSuicideGun = false;
bool UnlimitedAmmoSuicideGun = false;
bool UnlimitedAmmoShotGun = false;
bool UnlimitedAmmoRocketLauncher = false;
bool UnlimitedAmmoMachineGun = false;
bool UnlimitedAmmoGrenadeRifle = false;
bool UnlimitedAmmoAssaultRifle = false;

struct Patches{
    Patch *UnlimitedAmmoCrossbowPatch;
    Patch *UnlimitedAmmoElectricGunPatch;
    Patch *UnlimitedAmmoFireGunPatch;
    Patch *UnlimitedAmmoLaserGunPatch;
    Patch *UnlimitedAmmoSniperPatch;
    Patch *UnlimitedAmmoWeaponPatch;
    Patch *UnlimitedAmmoMultiSuicideGunPatch;
    Patch *UnlimitedAmmoSuicideGunPatch;
    Patch *UnlimitedAmmoShotGunPatch;
    Patch *UnlimitedAmmoRocketLauncherPatch;
    Patch *UnlimitedAmmoMachineGunPatch;
    Patch *UnlimitedAmmoGrenadeRiflePatch;
    Patch *UnlimitedAmmoAssaultRiflePatch;
}patch;




// we will run our patches in a new thread so our while loop doesn't block process main thread
void* hack_thread(void*) {
    LOGI("I have been loaded. Mwuahahahaha");
    // loop until our target library is found
    do {
        sleep(1);
    } while (!isLibraryLoaded(libName));
    LOGI("I found the il2cpp lib. Address is: %p", (void*)findLibrary(libName));
    LOGI("Hooking GameManager_LateUpdate");
    patch.UnlimitedAmmoCrossbowPatch = Patch::Setup((void*)getAbsoluteAddress(0x20D33C), (char*)"\x00\x00\xA0\xE3\x1e\xff\x2f\xe1", 8);
    patch.UnlimitedAmmoElectricGunPatch = Patch::Setup((void*)getAbsoluteAddress(0x210840), (char*)"\x00\x00\xA0\xE3\x1e\xff\x2f\xe1", 8);
    patch.UnlimitedAmmoLaserGunPatch = Patch::Setup((void*)getAbsoluteAddress(0x3263C4), (char*)"\x00\x00\xA0\xE3\x1e\xff\x2f\xe1", 8);
    patch.UnlimitedAmmoSniperPatch = Patch::Setup((void*)getAbsoluteAddress(0x51EE30), (char*)"\x00\x00\xA0\xE3\x1e\xff\x2f\xe1", 8);
    patch.UnlimitedAmmoWeaponPatch = Patch::Setup((void*)getAbsoluteAddress(0xB3A74C), (char*)"\x00\x00\xA0\xE3\x1e\xff\x2f\xe1", 8);
    patch.UnlimitedAmmoMultiSuicideGunPatch = Patch::Setup((void*)getAbsoluteAddress(0x4FB674), (char*)"\x00\x00\xA0\xE3\x1e\xff\x2f\xe1", 8);
    patch.UnlimitedAmmoSuicideGunPatch = Patch::Setup((void*)getAbsoluteAddress(0x51FA80), (char*)"\x00\x00\xA0\xE3\x1e\xff\x2f\xe1", 8);
    patch.UnlimitedAmmoShotGunPatch = Patch::Setup((void*)getAbsoluteAddress(0x51B6D8), (char*)"\x00\x00\xA0\xE3\x1e\xff\x2f\xe1", 8);
    patch.UnlimitedAmmoRocketLauncherPatch = Patch::Setup((void*)getAbsoluteAddress(0x514324), (char*)"\x00\x00\xA0\xE3\x1e\xff\x2f\xe1", 8);
    patch.UnlimitedAmmoMachineGunPatch = Patch::Setup((void*)getAbsoluteAddress(0x329338), (char*)"\x00\x00\xA0\xE3\x1e\xff\x2f\xe1", 8);
    patch.UnlimitedAmmoGrenadeRiflePatch = Patch::Setup((void*)getAbsoluteAddress(0x324768), (char*)"\x00\x00\xA0\xE3\x1e\xff\x2f\xe1", 8);
    patch.UnlimitedAmmoAssaultRiflePatch = Patch::Setup((void*)getAbsoluteAddress(0x2067F8), (char*)"\x00\x00\xA0\xE3\x1e\xff\x2f\xe1", 8);
    return NULL;
}

jobjectArray getListFT(JNIEnv *env, jclass jobj){
    jobjectArray ret;
    int i;
    const char *features[]= {"Unlimited Ammo - Crossbow", "Unlimited Ammo - Electric Gun", "Unlimited Ammo - Laser Gun", "Unlimited Ammo - Sniper", "Unlimited Ammo - Weapon", "Unlimited Ammo - Multi Suicide Gun", "Unlimited Ammo - Suicide Gun", "Unlimited Ammo - Shot Gun", "Unlimited Ammo - Rocket Launcher", "Unlimited Ammo - Machine Gun", "Unlimited Ammo - Grenade Rifle", "Unlimited Ammo - Assault Rifle"};
    int Total_Feature = (sizeof features / sizeof features[0]); //Now you dont have to manually update the number everytime
    ret= (jobjectArray)env->NewObjectArray(Total_Feature,
                                           env->FindClass("java/lang/String"),
                                           env->NewStringUTF(""));

    for(i=0;i<Total_Feature;i++) {
        env->SetObjectArrayElement(
                ret,i,env->NewStringUTF(features[i]));
    }
    return(ret);
}


void changeToggle(JNIEnv *env, jclass thisObj, jint number) {
    int i = (int) number;
    switch (i) {
        case 0:
            UnlimitedAmmoCrossbow = !UnlimitedAmmoCrossbow;
            if (UnlimitedAmmoCrossbow) {
                patch.UnlimitedAmmoCrossbowPatch->Apply();
            } else {
                patch.UnlimitedAmmoCrossbowPatch->Reset();
            }
            break;
        case 1:
            UnlimitedAmmoElectricGun = !UnlimitedAmmoElectricGun;
            if (UnlimitedAmmoElectricGun) {
                patch.UnlimitedAmmoElectricGunPatch->Apply();
            } else {
                patch.UnlimitedAmmoElectricGunPatch->Reset();
            }
        case 2:
            UnlimitedAmmoLaserGun = !UnlimitedAmmoLaserGun;
            if (UnlimitedAmmoLaserGun) {
                patch.UnlimitedAmmoLaserGunPatch->Apply();
            } else {
                patch.UnlimitedAmmoLaserGunPatch->Reset();
            }
        case 3:
            UnlimitedAmmoSniper = !UnlimitedAmmoSniper;
            if (UnlimitedAmmoSniper) {
                patch.UnlimitedAmmoSniperPatch->Apply();
            } else {
                patch.UnlimitedAmmoSniperPatch->Reset();
            }
        case 4:
            UnlimitedAmmoWeapon = !UnlimitedAmmoWeapon;
            if (UnlimitedAmmoWeapon) {
                patch.UnlimitedAmmoWeaponPatch->Apply();
            } else {
                patch.UnlimitedAmmoWeaponPatch->Reset();
            }
        case 5:
            UnlimitedAmmoMultiSuicideGun = !UnlimitedAmmoMultiSuicideGun;
            if (UnlimitedAmmoMultiSuicideGun) {
                patch.UnlimitedAmmoMultiSuicideGunPatch->Apply();
            } else {
                patch.UnlimitedAmmoMultiSuicideGunPatch->Reset();
            }
        case 6:
            UnlimitedAmmoSuicideGun = !UnlimitedAmmoSuicideGun;
            if (UnlimitedAmmoSuicideGun) {
                patch.UnlimitedAmmoSuicideGunPatch->Apply();
            } else {
                patch.UnlimitedAmmoSuicideGunPatch->Reset();
            }
        case 7:
            UnlimitedAmmoShotGun = !UnlimitedAmmoShotGun;
            if (UnlimitedAmmoShotGun) {
                patch.UnlimitedAmmoShotGunPatch->Apply();
            } else {
                patch.UnlimitedAmmoShotGunPatch->Reset();
            }
        case 8:
            UnlimitedAmmoRocketLauncher = !UnlimitedAmmoRocketLauncher;
            if (UnlimitedAmmoRocketLauncher) {
                patch.UnlimitedAmmoRocketLauncherPatch->Apply();
            } else {
                patch.UnlimitedAmmoRocketLauncherPatch->Reset();
            }
        case 9:
            UnlimitedAmmoMachineGun = !UnlimitedAmmoMachineGun;
            if (UnlimitedAmmoMachineGun) {
                patch.UnlimitedAmmoMachineGunPatch->Apply();
            } else {
                patch.UnlimitedAmmoMachineGunPatch->Reset();
            }
        case 10:
            UnlimitedAmmoGrenadeRifle = !UnlimitedAmmoGrenadeRifle;
            if (UnlimitedAmmoGrenadeRifle) {
                patch.UnlimitedAmmoGrenadeRiflePatch->Apply();
            } else {
                patch.UnlimitedAmmoGrenadeRiflePatch->Reset();
            }
        case 11:
            UnlimitedAmmoAssaultRifle = !UnlimitedAmmoAssaultRifle;
            if (UnlimitedAmmoAssaultRifle) {
                patch.UnlimitedAmmoAssaultRiflePatch->Apply();
            } else {
                patch.UnlimitedAmmoAssaultRiflePatch->Reset();
            }
        default:
            break;
    }
    return;
}


void init(JNIEnv * env, jclass obj, jobject thiz){
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
    MakeToast(env, thiz, "Mod by Greenphx");
}


extern "C"
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
JNIEnv* env;
if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
return JNI_ERR;
}

// Find your class. JNI_OnLoad is called from the correct class loader context for this to work.
jclass c = env->FindClass("com/dark/force/NativeLibrary");
if (c == nullptr) return JNI_ERR;

// Register your class' native methods.
static const JNINativeMethod methods[] = {
        {"changeToggle", "(I)V", reinterpret_cast<void*>(changeToggle)},
        {"getListFT", "()[Ljava/lang/String;", reinterpret_cast<void*>(getListFT)},
        {"init", "(Lcom/dark/force/MenuService;)V", reinterpret_cast<void*>(init)},
};
int rc = env->RegisterNatives(c, methods, sizeof(methods)/sizeof(JNINativeMethod));
if (rc != JNI_OK) return rc;

return JNI_VERSION_1_6;
}