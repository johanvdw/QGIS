/***************************************************************************
    qgsfillsymbollayerv2.h
    ---------------------
    begin                : November 2009
    copyright            : (C) 2009 by Martin Dobias
    email                : wonder dot sk at gmail dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSFILLSYMBOLLAYERV2_H
#define QGSFILLSYMBOLLAYERV2_H

#include "qgssymbollayerv2.h"

#define DEFAULT_SIMPLEFILL_COLOR        QColor(0,0,255)
#define DEFAULT_SIMPLEFILL_STYLE        Qt::SolidPattern
#define DEFAULT_SIMPLEFILL_BORDERCOLOR  QColor(0,0,0)
#define DEFAULT_SIMPLEFILL_BORDERSTYLE  Qt::SolidLine
#define DEFAULT_SIMPLEFILL_BORDERWIDTH  DEFAULT_LINE_WIDTH

#include <QPen>
#include <QBrush>

class CORE_EXPORT QgsSimpleFillSymbolLayerV2 : public QgsFillSymbolLayerV2
{
  public:
    QgsSimpleFillSymbolLayerV2( QColor color = DEFAULT_SIMPLEFILL_COLOR,
                                Qt::BrushStyle style = DEFAULT_SIMPLEFILL_STYLE,
                                QColor borderColor = DEFAULT_SIMPLEFILL_BORDERCOLOR,
                                Qt::PenStyle borderStyle = DEFAULT_SIMPLEFILL_BORDERSTYLE,
                                double borderWidth = DEFAULT_SIMPLEFILL_BORDERWIDTH );

    // static stuff

    static QgsSymbolLayerV2* create( const QgsStringMap& properties = QgsStringMap() );
    static QgsSymbolLayerV2* createFromSld( QDomElement &element );

    // implemented from base classes

    QString layerType() const;

    void startRender( QgsSymbolV2RenderContext& context );

    void stopRender( QgsSymbolV2RenderContext& context );

    void renderPolygon( const QPolygonF& points, QList<QPolygonF>* rings, QgsSymbolV2RenderContext& context );

    QgsStringMap properties() const;

    QgsSymbolLayerV2* clone() const;

    void toSld( QDomDocument &doc, QDomElement &element, QgsStringMap props ) const;

    QString ogrFeatureStyle( double mmScaleFactor, double mapUnitScaleFactor ) const;

    Qt::BrushStyle brushStyle() const { return mBrushStyle; }
    void setBrushStyle( Qt::BrushStyle style ) { mBrushStyle = style; }

    QColor borderColor() const { return mBorderColor; }
    void setBorderColor( QColor borderColor ) { mBorderColor = borderColor; }

    /** Get outline color.
     * @note added in 2.1 */
    QColor outlineColor() const { return borderColor(); }
    /** Set outline color.
     * @note added in 2.1 */
    void setOutlineColor( const QColor& color ) { setBorderColor( color ); }

    /** Get fill color.
     * @note added in 2.1 */
    QColor fillColor() const { return color(); }
    /** Set fill color.
     * @note added in 2.1 */
    void setFillColor( const QColor& color ) { setColor( color ); }

    Qt::PenStyle borderStyle() const { return mBorderStyle; }
    void setBorderStyle( Qt::PenStyle borderStyle ) { mBorderStyle = borderStyle; }

    double borderWidth() const { return mBorderWidth; }
    void setBorderWidth( double borderWidth ) { mBorderWidth = borderWidth; }

    void setOffset( QPointF offset ) { mOffset = offset; }
    QPointF offset() { return mOffset; }

    void setBorderWidthUnit( QgsSymbolV2::OutputUnit unit ) { mBorderWidthUnit = unit; }
    QgsSymbolV2::OutputUnit borderWidthUnit() const { return mBorderWidthUnit; }

    void setOffsetUnit( QgsSymbolV2::OutputUnit unit ) { mOffsetUnit = unit; }
    QgsSymbolV2::OutputUnit offsetUnit() const { return mOffsetUnit; }

    void setOutputUnit( QgsSymbolV2::OutputUnit unit );
    QgsSymbolV2::OutputUnit outputUnit() const;

    double estimateMaxBleed() const;

    double dxfWidth( const QgsDxfExport& e, const QgsSymbolV2RenderContext& context ) const;
    QColor dxfColor( const QgsSymbolV2RenderContext& context ) const;
    Qt::PenStyle dxfPenStyle() const;

  protected:
    QBrush mBrush;
    QBrush mSelBrush;
    Qt::BrushStyle mBrushStyle;
    QColor mBorderColor;
    Qt::PenStyle mBorderStyle;
    double mBorderWidth;
    QgsSymbolV2::OutputUnit mBorderWidthUnit;
    QPen mPen;
    QPen mSelPen;

    QPointF mOffset;
    QgsSymbolV2::OutputUnit mOffsetUnit;

  private:
    //helper functions for data defined symbology
    void applyDataDefinedSymbology( QgsSymbolV2RenderContext& context, QBrush& brush, QPen& pen, QPen& selPen );
};

class QgsVectorColorRampV2;

class CORE_EXPORT QgsGradientFillSymbolLayerV2 : public QgsFillSymbolLayerV2
{
  public:

    enum GradientColorType
    {
      SimpleTwoColor,
      ColorRamp
    };

    enum GradientType
    {
      Linear,
      Radial,
      Conical
    };

    enum GradientCoordinateMode
    {
      Feature,
      Viewport
    };

    enum GradientSpread
    {
      Pad,
      Reflect,
      Repeat
    };

    QgsGradientFillSymbolLayerV2( QColor color = DEFAULT_SIMPLEFILL_COLOR,
                                  QColor color2 = Qt::white,
                                  GradientColorType gradientColorType = SimpleTwoColor,
                                  GradientType gradientType = Linear,
                                  GradientCoordinateMode coordinateMode = Feature,
                                  GradientSpread gradientSpread = Pad
                                );

    virtual ~QgsGradientFillSymbolLayerV2();

    // static stuff

    static QgsSymbolLayerV2* create( const QgsStringMap& properties = QgsStringMap() );

    // implemented from base classes

    QString layerType() const;

    void startRender( QgsSymbolV2RenderContext& context );

    void stopRender( QgsSymbolV2RenderContext& context );

    void renderPolygon( const QPolygonF& points, QList<QPolygonF>* rings, QgsSymbolV2RenderContext& context );

    QgsStringMap properties() const;

    QgsSymbolLayerV2* clone() const;

    double estimateMaxBleed() const;

    /**Type of gradient, eg linear or radial*/
    GradientType gradientType() const { return mGradientType; };
    void setGradientType( GradientType gradientType ) { mGradientType = gradientType; };

    /**Gradient color mode, controls how gradient color stops are created*/
    GradientColorType gradientColorType() const { return mGradientColorType; };
    void setGradientColorType( GradientColorType gradientColorType ) { mGradientColorType = gradientColorType; };

    /**Color ramp used for the gradient fill, only used if the gradient color type is set to ColorRamp*/
    QgsVectorColorRampV2* colorRamp() { return mGradientRamp; };
    void setColorRamp( QgsVectorColorRampV2* ramp );

    /**Color for endpoint of gradient, only used if the gradient color type is set to SimpleTwoColor*/
    QColor color2() const { return mColor2; };
    void setColor2( QColor color2 ) { mColor2 = color2; };

    /**Coordinate mode for gradient. Controls how the gradient stops are positioned.*/
    GradientCoordinateMode coordinateMode() const { return mCoordinateMode; };
    void setCoordinateMode( GradientCoordinateMode coordinateMode ) { mCoordinateMode = coordinateMode; };

    /**Gradient spread mode. Controls how the gradient behaves outside of the predefined stops*/
    GradientSpread gradientSpread() const { return mGradientSpread; };
    void setGradientSpread( GradientSpread gradientSpread ) { mGradientSpread = gradientSpread; };

    /**Starting point of gradient fill, in the range [0,0] - [1,1]*/
    void setReferencePoint1( QPointF referencePoint ) { mReferencePoint1 = referencePoint; };
    QPointF referencePoint1() const { return mReferencePoint1; };

    /**Sets the starting point of the gradient to be the feature centroid*/
    void setReferencePoint1IsCentroid( bool isCentroid ) { mReferencePoint1IsCentroid = isCentroid; };
    bool referencePoint1IsCentroid() const { return mReferencePoint1IsCentroid; };

    /**End point of gradient fill, in the range [0,0] - [1,1]*/
    void setReferencePoint2( QPointF referencePoint ) { mReferencePoint2 = referencePoint; };
    QPointF referencePoint2() const { return mReferencePoint2; };

    /**Sets the end point of the gradient to be the feature centroid*/
    void setReferencePoint2IsCentroid( bool isCentroid ) { mReferencePoint2IsCentroid = isCentroid; };
    bool referencePoint2IsCentroid() const { return mReferencePoint2IsCentroid; };

    /**Rotation angle for gradient fill. Can be used to rotate a gradient around its centre point*/
    void setAngle( double angle ) { mAngle = angle; };
    double angle() const { return mAngle; };

    /**Offset for gradient fill*/
    void setOffset( QPointF offset ) { mOffset = offset; };
    QPointF offset() const { return mOffset; };

    /**Units for gradient fill offset*/
    void setOffsetUnit( QgsSymbolV2::OutputUnit unit ) { mOffsetUnit = unit; };
    QgsSymbolV2::OutputUnit offsetUnit() const { return mOffsetUnit; };

  protected:
    QBrush mBrush;
    QBrush mSelBrush;

    GradientColorType mGradientColorType;
    QColor mColor2;
    QgsVectorColorRampV2* mGradientRamp;
    GradientType mGradientType;
    GradientCoordinateMode mCoordinateMode;
    GradientSpread mGradientSpread;

    QPointF mReferencePoint1;
    bool mReferencePoint1IsCentroid;
    QPointF mReferencePoint2;
    bool mReferencePoint2IsCentroid;
    double mAngle;

    QPointF mOffset;
    QgsSymbolV2::OutputUnit mOffsetUnit;

  private:

    //helper functions for data defined symbology
    void applyDataDefinedSymbology( QgsSymbolV2RenderContext& context, const QPolygonF& points );

    /**Applies the gradient to a brush*/
    void applyGradient( const QgsSymbolV2RenderContext& context, QBrush& brush, const QColor& color, const QColor& color2,
                        const GradientColorType &gradientColorType, QgsVectorColorRampV2 *gradientRamp, const GradientType &gradientType,
                        const GradientCoordinateMode &coordinateMode, const GradientSpread &gradientSpread,
                        const QPointF &referencePoint1, const QPointF &referencePoint2, const double angle );

    /**rotates a reference point by a specified angle around the point (0.5, 0.5)*/
    QPointF rotateReferencePoint( const QPointF & refPoint, double angle );
};

/**Base class for polygon renderers generating texture images*/
class CORE_EXPORT QgsImageFillSymbolLayer: public QgsFillSymbolLayerV2
{
  public:
    QgsImageFillSymbolLayer();
    virtual ~QgsImageFillSymbolLayer();
    void renderPolygon( const QPolygonF& points, QList<QPolygonF>* rings, QgsSymbolV2RenderContext& context );

    virtual QgsSymbolV2* subSymbol() { return mOutline; }
    virtual bool setSubSymbol( QgsSymbolV2* symbol );

    void setOutlineWidthUnit( QgsSymbolV2::OutputUnit unit ) { mOutlineWidthUnit = unit; }
    QgsSymbolV2::OutputUnit outlineWidthUnit() const { return mOutlineWidthUnit; }

    virtual double estimateMaxBleed() const;

    virtual double dxfWidth( const QgsDxfExport& e, const QgsSymbolV2RenderContext& context ) const;
    virtual QColor dxfColor( const QgsSymbolV2RenderContext& context ) const;
    virtual Qt::PenStyle dxfPenStyle() const;

  protected:
    QBrush mBrush;
    double mNextAngle; // mAngle / data defined angle

    /**Outline width*/
    double mOutlineWidth;
    QgsSymbolV2::OutputUnit mOutlineWidthUnit;

    /**Custom outline*/
    QgsLineSymbolV2* mOutline;

    virtual void applyDataDefinedSettings( const QgsSymbolV2RenderContext& context ) { Q_UNUSED( context ); }
};

/**A class for svg fill patterns. The class automatically scales the pattern to
   the appropriate pixel dimensions of the output device*/
class CORE_EXPORT QgsSVGFillSymbolLayer: public QgsImageFillSymbolLayer
{
  public:
    QgsSVGFillSymbolLayer( const QString& svgFilePath = "", double width = 20, double rotation = 0.0 );
    QgsSVGFillSymbolLayer( const QByteArray& svgData, double width = 20, double rotation = 0.0 );
    ~QgsSVGFillSymbolLayer();

    static QgsSymbolLayerV2* create( const QgsStringMap& properties = QgsStringMap() );
    static QgsSymbolLayerV2* createFromSld( QDomElement &element );

    // implemented from base classes

    QString layerType() const;

    void startRender( QgsSymbolV2RenderContext& context );
    void stopRender( QgsSymbolV2RenderContext& context );

    QgsStringMap properties() const;

    QgsSymbolLayerV2* clone() const;

    void toSld( QDomDocument &doc, QDomElement &element, QgsStringMap props ) const;

    //getters and setters
    void setSvgFilePath( const QString& svgPath );
    QString svgFilePath() const { return mSvgFilePath; }
    void setPatternWidth( double width ) { mPatternWidth = width;}
    double patternWidth() const { return mPatternWidth; }

    void setSvgFillColor( const QColor& c ) { mSvgFillColor = c; }
    QColor svgFillColor() const { return mSvgFillColor; }
    void setSvgOutlineColor( const QColor& c ) { mSvgOutlineColor = c; }
    QColor svgOutlineColor() const { return mSvgOutlineColor; }
    void setSvgOutlineWidth( double w ) { mSvgOutlineWidth = w; }
    double svgOutlineWidth() const { return mSvgOutlineWidth; }

    void setPatternWidthUnit( QgsSymbolV2::OutputUnit unit ) { mPatternWidthUnit = unit; }
    QgsSymbolV2::OutputUnit patternWidthUnit() const { return mPatternWidthUnit; }

    void setSvgOutlineWidthUnit( QgsSymbolV2::OutputUnit unit ) { mSvgOutlineWidthUnit = unit; }
    QgsSymbolV2::OutputUnit svgOutlineWidthUnit() const { return mSvgOutlineWidthUnit; }

    void setOutputUnit( QgsSymbolV2::OutputUnit unit );
    QgsSymbolV2::OutputUnit outputUnit() const;

  protected:
    /**Width of the pattern (in output units)*/
    double mPatternWidth;
    QgsSymbolV2::OutputUnit mPatternWidthUnit;

    /**SVG data*/
    QByteArray mSvgData;
    /**Path to the svg file (or empty if constructed directly from data)*/
    QString mSvgFilePath;
    /**SVG view box (to keep the aspect ratio */
    QRectF mSvgViewBox;
    /** SVG pattern image
     * @note added in 1.9 */
    QImage* mSvgPattern;

    //param(fill), param(outline), param(outline-width) are going
    //to be replaced in memory
    QColor mSvgFillColor;
    QColor mSvgOutlineColor;
    double mSvgOutlineWidth;
    QgsSymbolV2::OutputUnit mSvgOutlineWidthUnit;

    void applyDataDefinedSettings( const QgsSymbolV2RenderContext& context );

  private:
    /**Helper function that gets the view box from the byte array*/
    void storeViewBox();
    void setDefaultSvgParams(); //fills mSvgFillColor, mSvgOutlineColor, mSvgOutlineWidth with default values for mSvgFilePath

    /**Applies the svg pattern to the brush*/
    void applyPattern( QBrush& brush, const QString& svgFilePath, double patternWidth, QgsSymbolV2::OutputUnit patternWidthUnit, const QColor& svgFillColor, const QColor& svgOutlineColor,
                       double svgOutlineWidth, QgsSymbolV2::OutputUnit svgOutlineWidthUnit, const QgsSymbolV2RenderContext& context );
};

class CORE_EXPORT QgsLinePatternFillSymbolLayer: public QgsImageFillSymbolLayer
{
  public:
    QgsLinePatternFillSymbolLayer();
    ~QgsLinePatternFillSymbolLayer();

    static QgsSymbolLayerV2* create( const QgsStringMap& properties = QgsStringMap() );
    static QgsSymbolLayerV2* createFromSld( QDomElement &element );

    QString layerType() const;

    void startRender( QgsSymbolV2RenderContext& context );

    void stopRender( QgsSymbolV2RenderContext& context );

    QgsStringMap properties() const;

    QgsSymbolLayerV2* clone() const;

    void toSld( QDomDocument &doc, QDomElement &element, QgsStringMap props ) const;

    double estimateMaxBleed() const;

    QString ogrFeatureStyleWidth( double widthScaleFactor ) const;

    //getters and setters
    void setLineAngle( double a ) { mLineAngle = a; }
    double lineAngle() const { return mLineAngle; }
    void setDistance( double d ) { mDistance = d; }
    double distance() const { return mDistance; }
    void setLineWidth( double w ) { mLineWidth = w; }
    double lineWidth() const { return mLineWidth; }
    void setColor( const QColor& c ) { mColor = c; }
    QColor color() const { return mColor; }
    void setOffset( double offset ) { mOffset = offset; }
    double offset() const { return mOffset; }

    void setDistanceUnit( QgsSymbolV2::OutputUnit unit ) { mDistanceUnit = unit; }
    QgsSymbolV2::OutputUnit distanceUnit() const { return mDistanceUnit; }

    void setLineWidthUnit( QgsSymbolV2::OutputUnit unit ) { mLineWidthUnit = unit; }
    QgsSymbolV2::OutputUnit lineWidthUnit() const { return mLineWidthUnit; }

    void setOffsetUnit( QgsSymbolV2::OutputUnit unit ) { mOffsetUnit = unit; }
    QgsSymbolV2::OutputUnit offsetUnit() const { return mOffsetUnit; }

    void setOutputUnit( QgsSymbolV2::OutputUnit unit );
    QgsSymbolV2::OutputUnit outputUnit() const;

    bool setSubSymbol( QgsSymbolV2* symbol );
    QgsSymbolV2* subSymbol();

  protected:
    /**Distance (in mm or map units) between lines*/
    double mDistance;
    QgsSymbolV2::OutputUnit mDistanceUnit;
    /**Line width (in mm or map units)*/
    double mLineWidth;
    QgsSymbolV2::OutputUnit mLineWidthUnit;
    QColor mColor;
    /**Vector line angle in degrees (0 = horizontal, counterclockwise)*/
    double mLineAngle;
    /**Offset perpendicular to line direction*/
    double mOffset;
    QgsSymbolV2::OutputUnit mOffsetUnit;

    void applyDataDefinedSettings( const QgsSymbolV2RenderContext& context );

  private:
    /**Applies the svg pattern to the brush*/
    void applyPattern( const QgsSymbolV2RenderContext& context, QBrush& brush, double lineAngle, double distance, double lineWidth, const QColor& color );

    /**Fill line*/
    QgsLineSymbolV2* mFillLineSymbol;
};

class CORE_EXPORT QgsPointPatternFillSymbolLayer: public QgsImageFillSymbolLayer
{
  public:
    QgsPointPatternFillSymbolLayer();
    ~QgsPointPatternFillSymbolLayer();

    static QgsSymbolLayerV2* create( const QgsStringMap& properties = QgsStringMap() );
    static QgsSymbolLayerV2* createFromSld( QDomElement &element );

    QString layerType() const;

    void startRender( QgsSymbolV2RenderContext& context );

    void stopRender( QgsSymbolV2RenderContext& context );

    QgsStringMap properties() const;

    QgsSymbolLayerV2* clone() const;

    void toSld( QDomDocument &doc, QDomElement &element, QgsStringMap props ) const;

    double estimateMaxBleed() const;

    //getters and setters
    double distanceX() const { return mDistanceX; }
    void setDistanceX( double d ) { mDistanceX = d; }

    double distanceY() const { return mDistanceY; }
    void setDistanceY( double d ) { mDistanceY = d; }

    double displacementX() const { return mDisplacementX; }
    void setDisplacementX( double d ) { mDisplacementX = d; }

    double displacementY() const { return mDisplacementY; }
    void setDisplacementY( double d ) { mDisplacementY = d; }

    bool setSubSymbol( QgsSymbolV2* symbol );
    virtual QgsSymbolV2* subSymbol() { return mMarkerSymbol; }

    void setDistanceXUnit( QgsSymbolV2::OutputUnit unit ) { mDistanceXUnit = unit; }
    QgsSymbolV2::OutputUnit distanceXUnit() const { return mDistanceXUnit; }

    void setDistanceYUnit( QgsSymbolV2::OutputUnit unit ) { mDistanceYUnit = unit; }
    QgsSymbolV2::OutputUnit distanceYUnit() const { return mDistanceYUnit; }

    void setDisplacementXUnit( QgsSymbolV2::OutputUnit unit ) { mDisplacementXUnit = unit; }
    QgsSymbolV2::OutputUnit displacementXUnit() const { return mDisplacementXUnit; }

    void setDisplacementYUnit( QgsSymbolV2::OutputUnit unit ) { mDisplacementYUnit = unit; }
    QgsSymbolV2::OutputUnit displacementYUnit() const { return mDisplacementYUnit; }

    void setOutputUnit( QgsSymbolV2::OutputUnit unit );
    QgsSymbolV2::OutputUnit outputUnit() const;

  protected:
    QgsMarkerSymbolV2* mMarkerSymbol;
    double mDistanceX;
    QgsSymbolV2::OutputUnit mDistanceXUnit;
    double mDistanceY;
    QgsSymbolV2::OutputUnit mDistanceYUnit;
    double mDisplacementX;
    QgsSymbolV2::OutputUnit mDisplacementXUnit;
    double mDisplacementY;
    QgsSymbolV2::OutputUnit mDisplacementYUnit;

    void applyDataDefinedSettings( const QgsSymbolV2RenderContext& context );

  private:
    void applyPattern( const QgsSymbolV2RenderContext& context, QBrush& brush, double distanceX, double distanceY,
                       double displacementX, double displacementY );
};

class CORE_EXPORT QgsCentroidFillSymbolLayerV2 : public QgsFillSymbolLayerV2
{
  public:
    QgsCentroidFillSymbolLayerV2();
    ~QgsCentroidFillSymbolLayerV2();

    // static stuff

    static QgsSymbolLayerV2* create( const QgsStringMap& properties = QgsStringMap() );
    static QgsSymbolLayerV2* createFromSld( QDomElement &element );

    // implemented from base classes

    QString layerType() const;

    void startRender( QgsSymbolV2RenderContext& context );

    void stopRender( QgsSymbolV2RenderContext& context );

    void renderPolygon( const QPolygonF& points, QList<QPolygonF>* rings, QgsSymbolV2RenderContext& context );

    QgsStringMap properties() const;

    QgsSymbolLayerV2* clone() const;

    void toSld( QDomDocument &doc, QDomElement &element, QgsStringMap props ) const;

    void setColor( const QColor& color );

    QgsSymbolV2* subSymbol();
    bool setSubSymbol( QgsSymbolV2* symbol );

    void setOutputUnit( QgsSymbolV2::OutputUnit unit ) { Q_UNUSED( unit ); }
    QgsSymbolV2::OutputUnit outputUnit() const;

    virtual QSet<QString> usedAttributes() const;

  protected:
    QgsMarkerSymbolV2* mMarker;
};

#endif
