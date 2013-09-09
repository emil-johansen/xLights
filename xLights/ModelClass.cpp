/***************************************************************
 * Name:      ModelClass.cpp
 * Purpose:   Represents Display Model
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2012-10-22
 * Copyright: 2012 by Matt Brown
 * License:
     This file is part of xLights.

    xLights is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    xLights is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with xLights.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************/

#include "ModelClass.h"
#include <wx/msgdlg.h>
#include <wx/tokenzr.h>

void ModelClass::SetFromXml(wxXmlNode* ModelNode)
{
    wxString tempstr,channelstr;
    wxString customModel,RGBorder;
    long degrees, StartChannel, channel;
    size_t i;

    ModelXml=ModelNode;
    TreeDegrees=0;
    Nodes.clear();

    name=ModelNode->GetAttribute(wxT("name"));
    DisplayAs=ModelNode->GetAttribute(wxT("DisplayAs"));
    if (ModelNode->HasAttribute(wxT("StringType")))
    {
        // post 3.1.4
        StringType=ModelNode->GetAttribute(wxT("StringType"));
    }
    else
    {
        // 3.1.4 and earlier
        StringType=ModelNode->GetAttribute(wxT("Order"),wxT("RGB"))+wxT(" Nodes");
    }
    SingleNode=HasSingleNode(StringType);
    SingleChannel=HasSingleChannel(StringType);
    RGBorder=SingleNode ? "RGB" : RGBorder=StringType.Left(3);
    rgbidx[0]=std::max(RGBorder.Find('R'),0);
    rgbidx[1]=std::max(RGBorder.Find('G'),0);
    rgbidx[2]=std::max(RGBorder.Find('B'),0);

    tempstr=ModelNode->GetAttribute(wxT("parm1"));
    tempstr.ToLong(&parm1);
    tempstr=ModelNode->GetAttribute(wxT("parm2"));
    tempstr.ToLong(&parm2);
    tempstr=ModelNode->GetAttribute(wxT("parm3"));
    tempstr.ToLong(&parm3);
    tempstr=ModelNode->GetAttribute(wxT("StartChannel"),wxT("1"));
    tempstr.ToLong(&StartChannel);
    tempstr=ModelNode->GetAttribute(wxT("Dir"));
    IsLtoR=tempstr != wxT("R");
    if (ModelNode->HasAttribute(wxT("StartSide")))
    {
        tempstr=ModelNode->GetAttribute(wxT("StartSide"));
        isBotToTop = (tempstr == wxT("B"));
    }
    else
    {
        isBotToTop=true;
    }
    if (ModelNode->HasAttribute(wxT("CustomModel")))
    {
        customModel = ModelNode->GetAttribute(wxT("CustomModel"));
    }

    tempstr=ModelNode->GetAttribute(wxT("Antialias"),wxT("0"));
    tempstr.ToLong(&Antialias);
    AliasFactor=1 << Antialias;
    MyDisplay=IsMyDisplay(ModelNode);

    tempstr=ModelNode->GetAttribute(wxT("offsetXpct"),wxT("0"));
    tempstr.ToDouble(&offsetXpct);
    tempstr=ModelNode->GetAttribute(wxT("offsetYpct"),wxT("0"));
    tempstr.ToDouble(&offsetYpct);
    tempstr=ModelNode->GetAttribute(wxT("PreviewScale"),wxT("0.333"));
    tempstr.ToDouble(&PreviewScale);
    tempstr=ModelNode->GetAttribute(wxT("PreviewRotation"),wxT("0"));
    tempstr.ToLong(&degrees);
    PreviewRotation=degrees;

    // calculate starting channel numbers for each string
    size_t NumberOfStrings= HasOneString(DisplayAs) ? 1 : parm1;
    tempstr=ModelNode->GetAttribute(wxT("Advanced"),wxT("0"));
    bool HasIndividualStartChans=tempstr == wxT("1");
    int ChannelsPerString=parm2*3;
    if (SingleChannel)
        ChannelsPerString=1;
    else if (SingleNode)
        ChannelsPerString=3;
    stringStartChan.clear();
    stringStartChan.resize(NumberOfStrings);
    for (i=0; i<NumberOfStrings; i++)
    {
        tempstr=StartChanAttrName(i);
        if (HasIndividualStartChans && ModelNode->HasAttribute(tempstr))
        {
            ModelNode->GetAttribute(tempstr, &channelstr);
            channelstr.ToLong(&channel);
            stringStartChan[i] = channel-1;
        }
        else
        {
            stringStartChan[i] = StartChannel-1 + i*ChannelsPerString;
        }
    }

    // initialize model based on the DisplayAs value
    wxStringTokenizer tkz(DisplayAs, wxT(" "));
    wxString token = tkz.GetNextToken();
    if (token == wxT("Tree"))
    {
        InitVMatrix();
        token = tkz.GetNextToken();
        token.ToLong(&degrees);
        SetTreeCoord(degrees);
    }
    else if (DisplayAs == wxT("Custom"))
    {
        InitCustomMatrix(customModel);
        CopyBufCoord2ScreenCoord();
    }
    else if (DisplayAs == wxT("Vert Matrix"))
    {
        InitVMatrix();
        CopyBufCoord2ScreenCoord();
    }
    else if (DisplayAs == wxT("Horiz Matrix"))
    {
        InitHMatrix();
        CopyBufCoord2ScreenCoord();
    }
    else if (DisplayAs == wxT("Single Line"))
    {
        InitLine();
        SetLineCoord();
    }
    else if (DisplayAs == wxT("Arches"))
    {
        InitLine();
        SetArchCoord();
    }
    else if (DisplayAs == wxT("Window Frame"))
    {
        InitFrame();
        CopyBufCoord2ScreenCoord();
    }
    else if (DisplayAs == wxT("Star"))
    {
        InitStar();
        CopyBufCoord2ScreenCoord();
    }
    else if (DisplayAs == wxT("Wreath"))
    {
        InitWreath();
        CopyBufCoord2ScreenCoord();
    }

    size_t NodeCount=GetNodeCount();
    for(size_t i=0; i<NodeCount; i++)
    {
        Nodes[i]->sparkle = rand() % 10000;
    }
}

void ModelClass::GetChanIntensity(size_t nodenum, wxByte chidx, size_t *absChNum, uint8_t *intensity)
{
    Nodes[nodenum]->GetChanIntensity(chidx,rgbidx[chidx],absChNum,intensity);
}

void ModelClass::SetChanIntensity(size_t nodenum, wxByte chidx, uint8_t intensity)
{
    Nodes[nodenum]->SetChanIntensity(rgbidx[chidx],intensity);
}

void ModelClass::SetChanIntensityAll(size_t nodenum, uint8_t intensity)
{
    Nodes[nodenum]->SetChanIntensityAll(intensity);
}

// only valid for rgb nodes and dumb strings (not traditional strings)
wxChar ModelClass::GetChannelColorLetter(wxByte chidx)
{
    wxString rgb=wxT("RGB");
    return rgb[rgbidx[chidx]];
}

int ModelClass::GetLastChannel()
{
    int LastChan=0;
    size_t NodeCount=GetNodeCount();
    for(size_t idx=0; idx<NodeCount; idx++)
    {
        LastChan=std::max(LastChan,Nodes[idx]->ActChan+2);
    }
    return LastChan;
}

void ModelClass::SetOffset(double xPct, double yPct)
{
    offsetXpct=xPct;
    offsetYpct=yPct;
}


void ModelClass::AddOffset(double xPct, double yPct)
{
    offsetXpct+=xPct;
    offsetYpct+=yPct;
}


void ModelClass::SetScale(double newscale)
{
    PreviewScale=newscale;
}

double ModelClass::GetScale()
{
    return PreviewScale;
}

// initialize buffer coordinates
// parm1=NumStrings
// parm2=PixelsPerString
// parm3=StrandsPerString
void ModelClass::InitVMatrix()
{
    int y,x,idx,stringnum,segmentnum,yincr;
    int NumStrands=parm1*parm3;
    int PixelsPerStrand=parm2/parm3;
    int PixelsPerString=PixelsPerStrand*parm3;
    SetBufferSize(PixelsPerStrand,NumStrands);
    SetNodeCount(parm1,PixelsPerString);
    SetRenderSize(PixelsPerStrand,NumStrands);

    // create output mapping
    if (SingleNode) {
        x=0;
        for (size_t n=0; n<Nodes.size(); n++)
        {
            Nodes[n]->ActChan = stringStartChan[n];
            y=0;
            yincr=1;
            for (size_t c=0; c<PixelsPerString; c++)
            {
                Nodes[n]->Coords[c].bufX=IsLtoR ? x : NumStrands-x-1;
                Nodes[n]->Coords[c].bufY=y;
                y+=yincr;
                if (y < 0 || y >= PixelsPerStrand)
                {
                    yincr=-yincr;
                    y+=yincr;
                    x++;
                }
            }
        }
    } else {
        for (x=0; x < NumStrands; x++)
        {
            stringnum=x / parm3;
            segmentnum=x % parm3;
            for(y=0; y < PixelsPerStrand; y++)
            {
                idx=stringnum * PixelsPerString + segmentnum * PixelsPerStrand + y;
                Nodes[idx]->ActChan = stringStartChan[stringnum] + segmentnum * PixelsPerStrand*3 + y*3;
                Nodes[idx]->Coords[0].bufX=IsLtoR ? x : NumStrands-x-1;
                Nodes[idx]->Coords[0].bufY= isBotToTop == (segmentnum % 2 == 0) ? y:PixelsPerStrand-y-1;
                Nodes[idx]->StringNum=stringnum;
            }
        }
    }
}

// initialize buffer coordinates
// parm1=NumStrings
// parm2=PixelsPerString
// parm3=StrandsPerString
void ModelClass::InitHMatrix()
{
    int y,x,idx,stringnum,segmentnum,xincr;
    int NumStrands=parm1*parm3;
    int PixelsPerStrand=parm2/parm3;
    int PixelsPerString=PixelsPerStrand*parm3;
    SetBufferSize(NumStrands,PixelsPerStrand);
    SetNodeCount(parm1,PixelsPerString);
    SetRenderSize(NumStrands,PixelsPerStrand);

    // create output mapping
    if (SingleNode) {
        y=0;
        for (size_t n=0; n<Nodes.size(); n++)
        {
            Nodes[n]->ActChan = stringStartChan[n];
            x=0;
            xincr=1;
            for (size_t c=0; c<PixelsPerString; c++)
            {
                Nodes[n]->Coords[c].bufX=x;
                Nodes[n]->Coords[c].bufY=isBotToTop ? y :NumStrands-y-1;
                x+=xincr;
                if (x < 0 || x >= PixelsPerStrand)
                {
                    xincr=-xincr;
                    x+=xincr;
                    y++;
                }
            }
        }
    } else {
        for (y=0; y < NumStrands; y++)
        {
            stringnum=y / parm3;
            segmentnum=y % parm3;
            for(x=0; x<PixelsPerStrand; x++)
            {
                idx=stringnum * PixelsPerString + segmentnum * PixelsPerStrand + x;
                Nodes[idx]->ActChan = stringStartChan[stringnum] + segmentnum * PixelsPerStrand*3 + x*3;
                Nodes[idx]->Coords[0].bufX=IsLtoR != (segmentnum % 2 == 0) ? PixelsPerStrand-x-1 : x;
                Nodes[idx]->Coords[0].bufY= isBotToTop ? y :NumStrands-y-1;
                Nodes[idx]->StringNum=stringnum;
            }
        }
    }
}

void ModelClass::InitCustomMatrix(wxString customModel)
{
    wxString value;
    wxArrayString cols;
    long idx;
    int width=1;
    NodeBaseClass* newnode;

    wxArrayString rows=wxSplit(customModel,';');
    int height=rows.size();
    if (SingleNode) {
        SetNodeCount(1,0);
        Nodes[0]->ActChan=stringStartChan[0];
        for(size_t row=0; row < rows.size(); row++)
        {
            cols=wxSplit(rows[row],',');
            if (cols.size() > width) width=cols.size();
            for(size_t col=0; col < cols.size(); col++)
            {
                value=cols[col];
                if (!value.IsEmpty() && value != wxT("0"))
                {
                    Nodes[0]->AddBufCoord(col,height - row - 1);
                }
            }
        }
    } else {
        // rgb nodes
        for(size_t row=0; row < rows.size(); row++)
        {
            cols=wxSplit(rows[row],',');
            if (cols.size() > width) width=cols.size();
            for(size_t col=0; col < cols.size(); col++)
            {
                value=cols[col];
                if (!value.IsEmpty() && value != wxT("0"))
                {
                    // add a node
                    newnode=new NodeBaseClass();
                    newnode->StringNum=0;
                    value.ToLong(&idx);
                    newnode->ActChan=stringStartChan[0] + (idx-1) * 3;
                    Nodes.push_back(NodeBaseClassPtr(newnode));
                    Nodes.back()->AddBufCoord(col,height - row - 1);
                }
            }
        }
    }
    SetBufferSize(height,width);
}

double ModelClass::toRadians(long degrees)
{
    return 2.0*M_PI*double(degrees)/360.0;
}

// initialize screen coordinates for tree
void ModelClass::SetTreeCoord(long degrees)
{
    int bufferX, bufferY;
    double angle,x0;
    TreeDegrees=degrees;
    if (BufferWi < 2) return;
    if(BufferHt<1) return; // June 27,2013. added check to not divide by zero
    int factor=1000/BufferHt;
    RenderHt=BufferHt*factor;
    RenderWi=RenderHt/2;
    double radians=toRadians(degrees);
    double radius=RenderWi/2.0;
    double StartAngle=-radians/2.0;
    double AngleIncr=radians/double(BufferWi-1);
    //wxString msg=wxString::Format(wxT("BufferHt=%d, BufferWi=%d, factor=%d, RenderHt=%d, RenderWi=%d\n"),BufferHt,BufferWi,factor,RenderHt,RenderWi);
    size_t NodeCount=GetNodeCount();
    for(size_t n=0; n<NodeCount; n++)
    {
        size_t CoordCount=GetCoordCount(n);
        for(size_t c=0; c < CoordCount; c++)
        {
            bufferX=Nodes[n]->Coords[c].bufX;
            bufferY=Nodes[n]->Coords[c].bufY;
            angle=StartAngle + double(bufferX) * AngleIncr;
            x0=radius * sin(angle);
            Nodes[n]->Coords[c].screenX=floor(x0*(1.0-double(bufferY)/double(BufferHt)) + 0.5);
            Nodes[n]->Coords[c].screenY=bufferY * factor;
        }
    }
}

// initialize buffer coordinates
// parm1=Number of Strings/Arches
// parm2=Pixels Per String/Arch
void ModelClass::InitLine()
{
    SetNodeCount(parm1,parm2);
    SetBufferSize(1,parm2);
    int LastStringNum=-1;
    int chan,idx;
    int ChanIncr=SingleChannel ?  1 : 3;
    size_t NodeCount=GetNodeCount();
    for(size_t n=0; n<NodeCount; n++)
    {
        if (Nodes[n]->StringNum != LastStringNum)
        {
            LastStringNum=Nodes[n]->StringNum;
            chan=stringStartChan[LastStringNum];
            idx=0;
        }
        Nodes[n]->ActChan=chan;
        chan+=ChanIncr;
        size_t CoordCount=GetCoordCount(n);
        for(size_t c=0; c < CoordCount; c++)
        {
            Nodes[n]->Coords[c].bufX=IsLtoR ? idx : parm2-idx-1;
            Nodes[n]->Coords[c].bufY=0;
            idx++;
        }
    }
}

// parm3 is number of points
// top left=top ccw, top right=top cw, bottom left=bottom cw, bottom right=bottom ccw
void ModelClass::InitStar()
{
    if (parm3 < 2) parm3=2; // need at least 2 arms
    SetNodeCount(parm1,parm2);
    int numlights=parm1*parm2;
    SetBufferSize(numlights+1,numlights+1);
    int LastStringNum=-1;
    int chan,cursegment,nextsegment,x,y;
    int offset=numlights/2;
    int numsegments=parm3*2;
    double segstart_x,segstart_y,segend_x,segend_y,segstart_pct,segend_pct,r,angle,segpct,dseg;
    double dpct=1.0/(double)numsegments;
    double OuterRadius=offset;
    double InnerRadius=OuterRadius/2.618034;    // divide by golden ratio squared
    double pct=isBotToTop ? 0.5 : 0.0;          // % of circle, 0=top
    double pctIncr=1.0 / (double)numlights;     // this is cw
    if (IsLtoR != isBotToTop) pctIncr*=-1.0;    // adjust to ccw
    int ChanIncr=SingleChannel ?  1 : 3;
    size_t NodeCount=GetNodeCount();
    for(size_t n=0; n<NodeCount; n++)
    {
        if (Nodes[n]->StringNum != LastStringNum)
        {
            LastStringNum=Nodes[n]->StringNum;
            chan=stringStartChan[LastStringNum];
        }
        Nodes[n]->ActChan=chan;
        chan+=ChanIncr;
        size_t CoordCount=GetCoordCount(n);
        for(size_t c=0; c < CoordCount; c++)
        {
            cursegment=(int)((double)numsegments*pct) % numsegments;
            nextsegment=(cursegment+1) % numsegments;
            segstart_pct=(double)cursegment / numsegments;
            segend_pct=(double)nextsegment / numsegments;
            dseg=pct - segstart_pct;
            segpct=dseg / dpct;
            r=cursegment%2==0 ? OuterRadius : InnerRadius;
            segstart_x=r*sin(segstart_pct*2.0*M_PI);
            segstart_y=r*cos(segstart_pct*2.0*M_PI);
            r=nextsegment%2==0 ? OuterRadius : InnerRadius;
            segend_x=r*sin(segend_pct*2.0*M_PI);
            segend_y=r*cos(segend_pct*2.0*M_PI);
            // now interpolate between segstart and segend
            x=(segend_x - segstart_x)*segpct + segstart_x + offset + 0.5;
            y=(segend_y - segstart_y)*segpct + segstart_y + offset + 0.5;
            Nodes[n]->Coords[c].bufX=x;
            Nodes[n]->Coords[c].bufY=y;
            pct+=pctIncr;
            if (pct >= 1.0) pct-=1.0;
            if (pct < 0.0) pct+=1.0;
        }
    }
}

// top left=top ccw, top right=top cw, bottom left=bottom cw, bottom right=bottom ccw
void ModelClass::InitWreath()
{
    SetNodeCount(parm1,parm2);
    int numlights=parm1*parm2;
    SetBufferSize(numlights+1,numlights+1);
    int LastStringNum=-1;
    int offset=numlights/2;
    double r=offset;
    int chan,x,y;
    double pct=isBotToTop ? 0.5 : 0.0;          // % of circle, 0=top
    double pctIncr=1.0 / (double)numlights;     // this is cw
    if (IsLtoR != isBotToTop) pctIncr*=-1.0;    // adjust to ccw
    int ChanIncr=SingleChannel ?  1 : 3;
    size_t NodeCount=GetNodeCount();
    for(size_t n=0; n<NodeCount; n++)
    {
        if (Nodes[n]->StringNum != LastStringNum)
        {
            LastStringNum=Nodes[n]->StringNum;
            chan=stringStartChan[LastStringNum];
        }
        Nodes[n]->ActChan=chan;
        chan+=ChanIncr;
        size_t CoordCount=GetCoordCount(n);
        for(size_t c=0; c < CoordCount; c++)
        {
            x=r*sin(pct*2.0*M_PI) + offset + 0.5;
            y=r*cos(pct*2.0*M_PI) + offset + 0.5;
            Nodes[n]->Coords[c].bufX=x;
            Nodes[n]->Coords[c].bufY=y;
            pct+=pctIncr;
            if (pct >= 1.0) pct-=1.0;
            if (pct < 0.0) pct+=1.0;
        }
    }
}

// initialize screen coordinates
// parm1=Number of Strings/Arches
// parm2=Pixels Per String/Arch
void ModelClass::SetLineCoord()
{
    int x,y;
    int idx=0;
    size_t NodeCount=GetNodeCount();
    int numlights=parm1*parm2;
    int half=numlights/2;
    SetRenderSize(numlights*2,numlights);
    double radians=toRadians(PreviewRotation);
    for(size_t n=0; n<NodeCount; n++)
    {
        size_t CoordCount=GetCoordCount(n);
        for(size_t c=0; c < CoordCount; c++)
        {
            x=cos(radians)*idx;
            x=IsLtoR ? x - half : half - x;
            y=sin(radians)*idx;
            Nodes[n]->Coords[c].screenX=x;
            Nodes[n]->Coords[c].screenY=y + numlights;
            idx++;
        }
    }
}

// Set screen coordinates for arches
void ModelClass::SetArchCoord()
{
    int ns,x, xoffset;
    double angle;
    int numlights=parm1*parm2;
    size_t NodeCount=GetNodeCount();
    SetRenderSize(parm2,numlights*2);
    double midpt=parm2;
    double AngleIncr=M_PI / parm2;
    for(size_t n=0; n<NodeCount; n++)
    {
        angle=-1.0*M_PI/2.0;
        xoffset=Nodes[n]->StringNum*parm2*2 - numlights;
        x=0;
        size_t CoordCount=GetCoordCount(n);
        while (x<parm2)
        {
            for(size_t c=0; c < CoordCount; c++)
            {
                Nodes[n]->Coords[c].screenX=xoffset + (int)floor(midpt*sin(angle)+midpt);
                Nodes[n]->Coords[c].screenY=(int)floor(midpt*cos(angle)+0.5);
                angle+=AngleIncr;
                x++;
            }
        }
    }
}

// initialize buffer coordinates
// parm1=Nodes on Top
// parm2=Nodes left and right
// parm3=Nodes on Bottom
void ModelClass::InitFrame()
{
    int x,y,newx,newy;
    SetNodeCount(1,parm1+2*parm2+parm3);
    int FrameWidth=std::max(parm1,parm3)+2;
    SetBufferSize(parm2,FrameWidth);   // treat as outside of matrix
    //SetBufferSize(1,Nodes.size());   // treat as single string
    SetRenderSize(parm2,FrameWidth);
    int chan=stringStartChan[0];
    int ChanIncr=SingleChannel ?  1 : 3;

    int xincr[4]={0,1,0,-1};  // indexed by side
    int yincr[4]={1,0,-1,0};
    x=IsLtoR ? 0 : FrameWidth-1;
    y=isBotToTop ? 0 : parm2-1;
    int dir=1;            // 1=clockwise
    int side=x>0 ? 2 : 0; // 0=left, 1=top, 2=right, 3=bottom
    int SideIncr=1;       // 1=clockwise
    if (parm1 > parm3 && x>0 || parm3 > parm1 && x==0) {
        // counter-clockwise
        dir=-1;
        SideIncr=3;
    }

    // determine starting position
    if (parm1 > parm3) {
        // more nodes on top, must start at bottom
        y=0;
    } else if (parm3 > parm1) {
        // more nodes on bottom, must start at top
        y=parm2-1;
    } else {
        // equal top and bottom, can start in any corner
        // assume clockwise numbering
        if (x>0 && y==0) {
            // starting in lower right
            side=3;
        } else if (x==0 && y>0) {
            // starting in upper left
            side=1;
        }
    }

    size_t NodeCount=GetNodeCount();
    for(size_t n=0; n<NodeCount; n++)
    {
        Nodes[n]->ActChan=chan;
        chan+=ChanIncr;
        size_t CoordCount=GetCoordCount(n);
        for(size_t c=0; c < CoordCount; c++)
        {
            Nodes[n]->Coords[c].bufX=x;
            Nodes[n]->Coords[c].bufY=y;
            newx=x+xincr[side]*dir;
            newy=y+yincr[side]*dir;
            if (newx < 0 || newx >= FrameWidth || newy < 0 || newy >= parm2) {
                // move to the next side
                side=(side+SideIncr) % 4;
                newx=x+xincr[side]*dir;
                newy=y+yincr[side]*dir;
            }
            x=newx;
            y=newy;
        }
    }
}

void ModelClass::SetBufferSize(int NewHt, int NewWi)
{
    BufferHt=NewHt;
    BufferWi=NewWi;
}

void ModelClass::SetRenderSize(int NewHt, int NewWi)
{
    RenderHt=NewHt;
    RenderWi=NewWi;
}

// not valid for Frame or Custom
int ModelClass::NodesPerString()
{
    return SingleNode ? 1 : parm2;
}

int ModelClass::NodeStartChannel(size_t nodenum)
{
    return Nodes[nodenum]->ActChan;
}

int ModelClass::ChannelsPerNode()
{
    return SingleChannel ? 1 : 3;
}

// set size of Nodes vector and each Node's Coords vector
void ModelClass::SetNodeCount(size_t NumStrings, size_t NodesPerString)
{
    size_t n;
    if (SingleNode) {
        if (StringType==wxT("Single Color Red")) {
            for(n=0; n<NumStrings; n++)
                Nodes.push_back(NodeBaseClassPtr(new NodeClassRed(n,NodesPerString)));
        } else if (StringType==wxT("Single Color Green")) {
            for(n=0; n<NumStrings; n++)
                Nodes.push_back(NodeBaseClassPtr(new NodeClassGreen(n,NodesPerString)));
        } else if (StringType==wxT("Single Color Blue")) {
            for(n=0; n<NumStrings; n++)
                Nodes.push_back(NodeBaseClassPtr(new NodeClassBlue(n,NodesPerString)));
        } else if (StringType==wxT("Single Color White")) {
            for(n=0; n<NumStrings; n++)
                Nodes.push_back(NodeBaseClassPtr(new NodeClassWhite(n,NodesPerString)));
        } else {
            // 3 Channel RGB
            for(n=0; n<NumStrings; n++)
                Nodes.push_back(NodeBaseClassPtr(new NodeBaseClass(n,NodesPerString)));
        }
    }
    else
    {
        size_t numnodes=NumStrings*NodesPerString;
        for(n=0; n<numnodes; n++)
            Nodes.push_back(NodeBaseClassPtr(new NodeBaseClass(n/NodesPerString, 1)));
    }
}

bool ModelClass::CanRotate()
{
    return DisplayAs == wxT("Single Line");
}

void ModelClass::Rotate(int degrees)
{
    if (!CanRotate()) return;
    PreviewRotation=degrees;
    SetLineCoord();
}

int ModelClass::GetRotation()
{
    return PreviewRotation;
}


// returns a number where the first node is 1
int ModelClass::GetNodeNumber(size_t nodenum)
{
    if (nodenum >= Nodes.size()) return 0;
    //if (Nodes[nodenum].bufX < 0) return 0;
    int sn=Nodes[nodenum]->StringNum;
    return (Nodes[nodenum]->ActChan - stringStartChan[sn]) / 3 + sn*NodesPerString() + 1;
}

size_t ModelClass::GetNodeCount()
{
    return Nodes.size();
}

size_t ModelClass::GetCoordCount(size_t nodenum)
{
    return nodenum < Nodes.size() ? Nodes[nodenum]->Coords.size() : 0;
}

wxString ModelClass::ChannelLayoutHtml()
{
    size_t NodeCount=GetNodeCount();
    size_t i,idx;
    int n,x,y,s;
    wxString bgcolor;
    std::vector<int> chmap;
    chmap.resize(BufferHt * BufferWi,0);
    bool IsCustom = DisplayAs == wxT("Custom");
    wxString direction;
    if (IsCustom) {
        direction=wxT("n/a");
    } else if (!IsLtoR) {
        if(!isBotToTop)
            direction=wxT("Top Right");
        else
            direction=wxT("Bottom Right");
    } else {
        if (!isBotToTop)
            direction=wxT("Top Left");
        else
            direction=wxT("Bottom Left");
    }

    wxString html = wxT("<html><body><table border=0>");
    html+=wxT("<tr><td>Name:</td><td>")+name+wxT("</td></tr>");
    html+=wxT("<tr><td>Display As:</td><td>")+DisplayAs+wxT("</td></tr>");
    html+=wxT("<tr><td>String Type:</td><td>")+StringType+wxT("</td></tr>");
    html+=wxT("<tr><td>Start Corner:</td><td>")+direction+wxT("</td></tr>");
    html+=wxString::Format(wxT("<tr><td>Total nodes:</td><td>%d</td></tr>"),NodeCount);
    html+=wxString::Format(wxT("<tr><td>Height:</td><td>%d</td></tr>"),BufferHt);
    html+=wxT("</table><p>Node numbers starting with 1 followed by string number:</p><table border=1>");
    if (BufferHt == 1)
    {
        // single line or arch
        html+=wxT("<tr>");
        for(i=1; i<=NodeCount; i++)
        {
            n=IsLtoR ? i : NodeCount-i+1;
            s=Nodes[n-1]->StringNum+1;
            bgcolor=s%2 == 1 ? wxT("#ADD8E6") : wxT("#90EE90");
            html+=wxString::Format(wxT("<td bgcolor='")+bgcolor+wxT("'>n%ds%d</td>"),n,s);
        }
        html+=wxT("</tr>");
    }
    else if (BufferHt > 1)
    {
        // horizontal or vertical matrix or frame
        for(i=0; i<NodeCount; i++)
        {
            idx=Nodes[i]->Coords[0].bufY * BufferWi + Nodes[i]->Coords[0].bufX;
            if (idx < chmap.size()) chmap[idx]=GetNodeNumber(i);
        }
        for(y=BufferHt-1; y>=0; y--)
        {
            html+=wxT("<tr>");
            for(x=0; x<BufferWi; x++)
            {
                n=chmap[y*BufferWi+x];
                if (n==0)
                {
                    html+=wxT("<td></td>");
                }
                else
                {
                    s=Nodes[n-1]->StringNum+1;
                    bgcolor=s%2 == 1 ? wxT("#ADD8E6") : wxT("#90EE90");
                    html+=wxString::Format(wxT("<td bgcolor='")+bgcolor+wxT("'>n%ds%d</td>"),n,s);
                }
            }
            html+=wxT("</tr>");
        }
    }
    else
    {
        html+=wxT("<tr><td>Error - invalid height</td></tr>");
    }
    html+=wxT("</table></body></html>");
    return html;
}


// initialize screen coordinates
void ModelClass::CopyBufCoord2ScreenCoord()
{
    size_t NodeCount=GetNodeCount();
    int xoffset=BufferWi/2;
    for(size_t n=0; n<NodeCount; n++)
    {
        size_t CoordCount=GetCoordCount(n);
        for(size_t c=0; c < CoordCount; c++)
        {
            Nodes[n]->Coords[c].screenX = Nodes[n]->Coords[c].bufX - xoffset;
            Nodes[n]->Coords[c].screenY = Nodes[n]->Coords[c].bufY;
        }
    }
    SetRenderSize(BufferHt,BufferWi);
}

void ModelClass::UpdateXmlWithScale()
{
    ModelXml->DeleteAttribute(wxT("offsetXpct"));
    ModelXml->DeleteAttribute(wxT("offsetYpct"));
    ModelXml->DeleteAttribute(wxT("PreviewScale"));
    ModelXml->DeleteAttribute(wxT("PreviewRotation"));
    ModelXml->AddAttribute(wxT("offsetXpct"), wxString::Format(wxT("%6.4f"),offsetXpct));
    ModelXml->AddAttribute(wxT("offsetYpct"), wxString::Format(wxT("%6.4f"),offsetYpct));
    ModelXml->AddAttribute(wxT("PreviewScale"), wxString::Format(wxT("%6.4f"),PreviewScale));
    ModelXml->AddAttribute(wxT("PreviewRotation"), wxString::Format(wxT("%d"),PreviewRotation));
}

// display model using a single color
void ModelClass::DisplayModelOnWindow(wxWindow* window, const wxColour* color)
{
    size_t NodeCount=Nodes.size();
    wxCoord sx,sy;
    wxClientDC dc(window);
    wxPen pen;
    wxCoord w, h;

    dc.GetSize(&w, &h);
    double scale=RenderHt > RenderWi ? double(h) / RenderHt * PreviewScale : double(w) / RenderWi * PreviewScale;
    /*
    // this isn't an ideal scaling algorithm - room for improvement here
    double windowDiagonal=sqrt(w*w+h*h);
    double modelDiagonal=sqrt(RenderWi*RenderWi+RenderHt*RenderHt);
    double scale=windowDiagonal / modelDiagonal * PreviewScale;
    */
    dc.SetAxisOrientation(true,true);
    dc.SetDeviceOrigin(int(offsetXpct*w)+w/2,int(offsetYpct*h)+h-std::max((h-int(double(RenderHt-1)*scale))/2,1));
    dc.SetUserScale(scale,scale);

    pen.SetColour(*color);
    dc.SetPen(pen);
    for(size_t n=0; n<NodeCount; n++)
    {
        size_t CoordCount=GetCoordCount(n);
        for(size_t c=0; c < CoordCount; c++)
        {
            // draw node on screen
            sx=Nodes[n]->Coords[c].screenX;
            sy=Nodes[n]->Coords[c].screenY;
            dc.DrawPoint(sx,sy);
            //dc.DrawCircle(sx*factor,sy*factor,radius);
        }
    }
}

// display model using colors stored in each node
void ModelClass::DisplayModelOnWindow(wxWindow* window)
{
    size_t NodeCount=Nodes.size();
    wxCoord sx,sy;
    wxClientDC dc(window);
    wxPen pen;
    wxColour color;
    wxCoord w, h;

    dc.GetSize(&w, &h);
    double scale=RenderHt > RenderWi ? double(h) / RenderHt * PreviewScale : double(w) / RenderWi * PreviewScale;
    /*
    // this isn't an ideal scaling algorithm - room for improvement here
    double windowDiagonal=sqrt(w*w+h*h);
    double modelDiagonal=sqrt(RenderWi*RenderWi+RenderHt*RenderHt);
    double scale=windowDiagonal / modelDiagonal * PreviewScale;
    */
    dc.SetAxisOrientation(true,true);
    dc.SetDeviceOrigin(int(offsetXpct*w)+w/2,int(offsetYpct*h)+h-std::max((h-int(double(RenderHt-1)*scale))/2,1));
    dc.SetUserScale(scale,scale);

    for(size_t n=0; n<NodeCount; n++)
    {
        Nodes[n]->GetColor(color);
        pen.SetColour(color);
        dc.SetPen(pen);
        size_t CoordCount=GetCoordCount(n);
        for(size_t c=0; c < CoordCount; c++)
        {
            // draw node on screen
            sx=Nodes[n]->Coords[c].screenX;
            sy=Nodes[n]->Coords[c].screenY;
            dc.DrawPoint(sx,sy);
            //dc.DrawCircle(sx*factor,sy*factor,radius);
        }
    }
}

// uses DrawCircle instead of DrawPoint
void ModelClass::DisplayEffectOnWindow(wxWindow* window)
{
    wxPen pen;
    wxBrush brush;
    wxClientDC dc(window);
    wxColour color;
    wxCoord w, h;
    dc.GetSize(&w, &h);
    double scaleX = double(w) / RenderWi;
    double scaleY = double(h) / RenderHt;
    double scale=scaleY < scaleX ? scaleY : scaleX;
    dc.SetAxisOrientation(true,true);
    dc.SetDeviceOrigin(w/2,h-std::max((h-int(double(RenderHt-1)*scale))/2,1));

    int radius=1;
    int factor=8;
    if (scale < 0.5)
    {
        radius=int(1.0/scale+0.5);
        factor=1;
    }
    else if (scale < 8.0)
    {
        factor=int(scale+0.5);
    }
    dc.SetUserScale(scale/factor,scale/factor);

    // if the radius/factor are not yielding good results, uncomment the next line
    //StatusBar1->SetStatusText(wxString::Format(wxT("Scale=%5.3f, radius=%d, factor=%d"),scale,radius,factor));

    /*
            // check that origin is in the right place
            dc.SetUserScale(4,4);
            color.Set(0,0,255);
            pen.SetColour(color);
            dc.SetPen(pen);
            dc.DrawPoint(0,0);
            dc.DrawPoint(1,1);
            dc.DrawPoint(2,2);
            return;
    */
    // layer calculation and map to output
    size_t NodeCount=Nodes.size();
    double sx,sy;

    for(size_t n=0; n<NodeCount; n++)
    {
        Nodes[n]->GetColor(color);
        pen.SetColour(color);
        brush.SetColour(color);
        brush.SetStyle(wxBRUSHSTYLE_SOLID);
        dc.SetPen(pen);
        dc.SetBrush(brush);
        size_t CoordCount=GetCoordCount(n);
        for(size_t c=0; c < CoordCount; c++)
        {
            // draw node on screen
            sx=Nodes[n]->Coords[c].screenX;
            sy=Nodes[n]->Coords[c].screenY;
            //#     dc.DrawPoint(Nodes[i].screenX, Nodes[i].screenY);
            //dc.DrawPoint(sx,sy);
            dc.DrawCircle(sx*factor,sy*factor,radius);
        }
    }
}
