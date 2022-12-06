#include <QCoreApplication>



bool isValidPayload(QString str){
   if(str.length() == 0 || str.length() % 2 == 1)
       return false;
   return true;
}

bool isValidMask(QString str){
   return isValidPayload(str) && str.length() / 2 == 8;
}

bool isValidLength(int len){
    return len >= 0 && len <= 8;
}

QString getMaskFromLength(QString mask,int len){
    Q_ASSERT(isValidMask(mask));
    Q_ASSERT(isValidLength(len));
    QString section = mask.mid(0,len * 2);
    return section;
}

uint64_t getFinalMask(QString mask){
    bool ok;
    uint64_t maskValue = mask.toULongLong(&ok,16);
    Q_ASSERT(ok == true);
    int shiftBits = __builtin_ctzll(maskValue);
    maskValue >>= shiftBits;
    return maskValue;
}

uint64_t getValueFromPayload(QString payload){
    bool ok;
    uint64_t value = payload.toULongLong(&ok,16);
    Q_ASSERT(ok == true);
    return value;
}

QString getConvertedValue(QString payload,QString mask,int length,int type){
    Q_ASSERT(isValidPayload(payload));
    Q_ASSERT(isValidMask(mask));
    Q_ASSERT(isValidLength(length));
    uint64_t rawValue = getValueFromPayload(payload);
    uint64_t finalMask = getFinalMask(getMaskFromLength(mask,length));
    return "";
    //return rawValue & finalMask;
}





int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Q_ASSERT(isValidPayload("00FF") == true);
    Q_ASSERT(isValidPayload("0FF") == false);
    Q_ASSERT(isValidPayload("") == false);

    Q_ASSERT(isValidMask("FF") == false);
    Q_ASSERT(isValidMask("00FF00FF00FF00FF") == true);

    Q_ASSERT(getMaskFromLength("00FF00FF00FF00FF",3) == "00FF00");
    Q_ASSERT(getFinalMask("00FF00") == 0xFF);
    Q_ASSERT(getValueFromPayload("0A0B") == 0x0A0B);
    return 0;
}
