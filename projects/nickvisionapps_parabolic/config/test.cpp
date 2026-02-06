#include <iostream>
#include "models/audiocodec.h"
#include "models/videocodec.h"
#include "models/mediatype.h"
#include "models/pathtype.h"
#include "models/subtitleformat.h"
#include "models/downloadstatus.h"
#include "models/credentialcheckstatus.h"
#include "models/historylength.h"
#include "models/formatvalue.h"

using namespace Nickvision::TubeConverter::Shared::Models;

int main() {
    AudioCodec a = AudioCodec::MP3;
    VideoCodec v = VideoCodec::H264;
    MediaType mt = MediaType::Video;
    PathType pt = PathType::Absolute;
    SubtitleFormat sf = SubtitleFormat::SRT;
    DownloadStatus ds = DownloadStatus::Queued;
    CredentialCheckStatus cs = CredentialCheckStatus::Valid;
    HistoryLength hl = HistoryLength::OneWeek;
    FormatValue fv = FormatValue::Best;

    std::cout << "Enums: "
              << (int)a << ", " << (int)v << ", " << (int)mt << ", " << (int)pt
              << ", " << (int)sf << ", " << (int)ds << ", " << (int)cs
              << ", " << (int)hl << ", " << (int)fv << std::endl;
    return 0;
}
