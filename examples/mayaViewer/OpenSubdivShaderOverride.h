//
//   Copyright 2013 Pixar
//
//   Licensed under the Apache License, Version 2.0 (the "Apache License")
//   with the following modification; you may not use this file except in
//   compliance with the Apache License and the following modification to it:
//   Section 6. Trademarks. is deleted and replaced with:
//
//   6. Trademarks. This License does not grant permission to use the trade
//      names, trademarks, service marks, or product names of the Licensor
//      and its affiliates, except as required to comply with Section 4(c) of
//      the License and to reproduce the content of the NOTICE file.
//
//   You may obtain a copy of the Apache License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the Apache License with the above modification is
//   distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
//   KIND, either express or implied. See the Apache License for the specific
//   language governing permissions and limitations under the Apache License.
//

#ifndef EXAMPLES_MAYAVIEWER_OPENSUBDIVSHADEROVERRIDE_H_
#define EXAMPLES_MAYAVIEWER_OPENSUBDIVSHADEROVERRIDE_H_

#include <maya/MPxShaderOverride.h>
#include <maya/MCallbackIdArray.h>

class OpenSubdivShader;
class OsdMeshData;

class OpenSubdivShaderOverride : public MHWRender::MPxShaderOverride 
{
public:
    static MHWRender::MPxShaderOverride* creator(const MObject &obj);

    virtual ~OpenSubdivShaderOverride();

    virtual MString initialize(const MInitContext &initContext,
                               MInitFeedback &initFeedback);

    virtual void updateDG(MObject object);

    virtual void updateDevice();

    virtual void endUpdate();

    virtual bool draw(MHWRender::MDrawContext &context,
                      const MHWRender::MRenderItemList &renderItemList) const;

    virtual bool rebuildAlways() { return false; }
    virtual MHWRender::DrawAPI  supportedDrawAPIs() const { return MHWRender::kOpenGL; }
    virtual bool isTransparent() { return true; }

    static void attrChangedCB(MNodeMessage::AttributeMessage msg, MPlug& plug, MPlug& otherPlug, void* );
    void addTopologyChangedCallbacks( const MDagPath& dagPath, OsdMeshData *data );

private:
    explicit OpenSubdivShaderOverride(const MObject &obj);

    OpenSubdivShader *_shader;

    MCallbackIdArray _callbackIds;
};

#endif  // EXAMPLES_MAYAVIEWER_OPENSUBDIVSHADEROVERRIDE_H_
