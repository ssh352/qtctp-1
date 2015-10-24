QWT_VER_MAJ      = 6
QWT_VER_MIN      = 1
QWT_VER_PAT      = 2
QWT_VERSION      = $${QWT_VER_MAJ}.$${QWT_VER_MIN}.$${QWT_VER_PAT}

QWT_CONFIG       += QwtPlot

QWT_SRC = $$PWD/qwt/src

INCLUDEPATH += \
    $$QWT_SRC

HEADERS += \
    $$QWT_SRC/qwt.h \
    $$QWT_SRC/qwt_abstract_scale_draw.h \
    $$QWT_SRC/qwt_clipper.h \
    $$QWT_SRC/qwt_color_map.h \
    $$QWT_SRC/qwt_compat.h \
    $$QWT_SRC/qwt_column_symbol.h \
    $$QWT_SRC/qwt_date.h \
    $$QWT_SRC/qwt_date_scale_draw.h \
    $$QWT_SRC/qwt_date_scale_engine.h \
    $$QWT_SRC/qwt_dyngrid_layout.h \
    $$QWT_SRC/qwt_global.h \
    $$QWT_SRC/qwt_graphic.h \
    $$QWT_SRC/qwt_interval.h \
    $$QWT_SRC/qwt_interval_symbol.h \
    $$QWT_SRC/qwt_math.h \
    $$QWT_SRC/qwt_magnifier.h \
    $$QWT_SRC/qwt_null_paintdevice.h \
    $$QWT_SRC/qwt_painter.h \
    $$QWT_SRC/qwt_painter_command.h \
    $$QWT_SRC/qwt_panner.h \
    $$QWT_SRC/qwt_picker.h \
    $$QWT_SRC/qwt_picker_machine.h \
    $$QWT_SRC/qwt_pixel_matrix.h \
    $$QWT_SRC/qwt_point_3d.h \
    $$QWT_SRC/qwt_point_polar.h \
    $$QWT_SRC/qwt_round_scale_draw.h \
    $$QWT_SRC/qwt_scale_div.h \
    $$QWT_SRC/qwt_scale_draw.h \
    $$QWT_SRC/qwt_scale_engine.h \
    $$QWT_SRC/qwt_scale_map.h \
    $$QWT_SRC/qwt_spline.h \
    $$QWT_SRC/qwt_symbol.h \
    $$QWT_SRC/qwt_system_clock.h \
    $$QWT_SRC/qwt_text_engine.h \
    $$QWT_SRC/qwt_text_label.h \
    $$QWT_SRC/qwt_text.h \
    $$QWT_SRC/qwt_transform.h \
    $$QWT_SRC/qwt_widget_overlay.h

SOURCES += \
    $$QWT_SRC/qwt_abstract_scale_draw.cpp \
    $$QWT_SRC/qwt_clipper.cpp \
    $$QWT_SRC/qwt_color_map.cpp \
    $$QWT_SRC/qwt_column_symbol.cpp \
    $$QWT_SRC/qwt_date.cpp \
    $$QWT_SRC/qwt_date_scale_draw.cpp \
    $$QWT_SRC/qwt_date_scale_engine.cpp \
    $$QWT_SRC/qwt_dyngrid_layout.cpp \
    $$QWT_SRC/qwt_event_pattern.cpp \
    $$QWT_SRC/qwt_graphic.cpp \
    $$QWT_SRC/qwt_interval.cpp \
    $$QWT_SRC/qwt_interval_symbol.cpp \
    $$QWT_SRC/qwt_math.cpp \
    $$QWT_SRC/qwt_magnifier.cpp \
    $$QWT_SRC/qwt_null_paintdevice.cpp \
    $$QWT_SRC/qwt_painter.cpp \
    $$QWT_SRC/qwt_painter_command.cpp \
    $$QWT_SRC/qwt_panner.cpp \
    $$QWT_SRC/qwt_picker.cpp \
    $$QWT_SRC/qwt_picker_machine.cpp \
    $$QWT_SRC/qwt_pixel_matrix.cpp \
    $$QWT_SRC/qwt_point_3d.cpp \
    $$QWT_SRC/qwt_point_polar.cpp \
    $$QWT_SRC/qwt_round_scale_draw.cpp \
    $$QWT_SRC/qwt_scale_div.cpp \
    $$QWT_SRC/qwt_scale_draw.cpp \
    $$QWT_SRC/qwt_scale_map.cpp \
    $$QWT_SRC/qwt_spline.cpp \
    $$QWT_SRC/qwt_scale_engine.cpp \
    $$QWT_SRC/qwt_symbol.cpp \
    $$QWT_SRC/qwt_system_clock.cpp \
    $$QWT_SRC/qwt_text_engine.cpp \
    $$QWT_SRC/qwt_text_label.cpp \
    $$QWT_SRC/qwt_text.cpp \
    $$QWT_SRC/qwt_transform.cpp \
    $$QWT_SRC/qwt_widget_overlay.cpp


contains(QWT_CONFIG, QwtPlot) {

    HEADERS += \
        $$QWT_SRC/qwt_curve_fitter.h \
        $$QWT_SRC/qwt_event_pattern.h \
        $$QWT_SRC/qwt_abstract_legend.h \
        $$QWT_SRC/qwt_legend.h \
        $$QWT_SRC/qwt_legend_data.h \
        $$QWT_SRC/qwt_legend_label.h \
        $$QWT_SRC/qwt_plot.h \
        $$QWT_SRC/qwt_plot_renderer.h \
        $$QWT_SRC/qwt_plot_curve.h \
        $$QWT_SRC/qwt_plot_dict.h \
        $$QWT_SRC/qwt_plot_directpainter.h \
        $$QWT_SRC/qwt_plot_grid.h \
        $$QWT_SRC/qwt_plot_histogram.h \
        $$QWT_SRC/qwt_plot_item.h \
        $$QWT_SRC/qwt_plot_abstract_barchart.h \
        $$QWT_SRC/qwt_plot_barchart.h \
        $$QWT_SRC/qwt_plot_multi_barchart.h \
        $$QWT_SRC/qwt_plot_intervalcurve.h \
        $$QWT_SRC/qwt_plot_tradingcurve.h \
        $$QWT_SRC/qwt_plot_layout.h \
        $$QWT_SRC/qwt_plot_marker.h \
        $$QWT_SRC/qwt_plot_zoneitem.h \
        $$QWT_SRC/qwt_plot_textlabel.h \
        $$QWT_SRC/qwt_plot_rasteritem.h \
        $$QWT_SRC/qwt_plot_spectrogram.h \
        $$QWT_SRC/qwt_plot_spectrocurve.h \
        $$QWT_SRC/qwt_plot_scaleitem.h \
        $$QWT_SRC/qwt_plot_legenditem.h \
        $$QWT_SRC/qwt_plot_seriesitem.h \
        $$QWT_SRC/qwt_plot_shapeitem.h \
        $$QWT_SRC/qwt_plot_canvas.h \
        $$QWT_SRC/qwt_plot_panner.h \
        $$QWT_SRC/qwt_plot_picker.h \
        $$QWT_SRC/qwt_plot_zoomer.h \
        $$QWT_SRC/qwt_plot_magnifier.h \
        $$QWT_SRC/qwt_plot_rescaler.h \
        $$QWT_SRC/qwt_point_mapper.h \
        $$QWT_SRC/qwt_raster_data.h \
        $$QWT_SRC/qwt_matrix_raster_data.h \
        $$QWT_SRC/qwt_sampling_thread.h \
        $$QWT_SRC/qwt_samples.h \
        $$QWT_SRC/qwt_series_data.h \
        $$QWT_SRC/qwt_series_store.h \
        $$QWT_SRC/qwt_point_data.h \
        $$QWT_SRC/qwt_scale_widget.h

    SOURCES += \
        $$QWT_SRC/qwt_curve_fitter.cpp \
        $$QWT_SRC/qwt_abstract_legend.cpp \
        $$QWT_SRC/qwt_legend.cpp \
        $$QWT_SRC/qwt_legend_data.cpp \
        $$QWT_SRC/qwt_legend_label.cpp \
        $$QWT_SRC/qwt_plot.cpp \
        $$QWT_SRC/qwt_plot_renderer.cpp \
        $$QWT_SRC/qwt_plot_xml.cpp \
        $$QWT_SRC/qwt_plot_axis.cpp \
        $$QWT_SRC/qwt_plot_curve.cpp \
        $$QWT_SRC/qwt_plot_dict.cpp \
        $$QWT_SRC/qwt_plot_directpainter.cpp \
        $$QWT_SRC/qwt_plot_grid.cpp \
        $$QWT_SRC/qwt_plot_histogram.cpp \
        $$QWT_SRC/qwt_plot_item.cpp \
        $$QWT_SRC/qwt_plot_abstract_barchart.cpp \
        $$QWT_SRC/qwt_plot_barchart.cpp \
        $$QWT_SRC/qwt_plot_multi_barchart.cpp \
        $$QWT_SRC/qwt_plot_intervalcurve.cpp \
        $$QWT_SRC/qwt_plot_zoneitem.cpp \
        $$QWT_SRC/qwt_plot_tradingcurve.cpp \
        $$QWT_SRC/qwt_plot_spectrogram.cpp \
        $$QWT_SRC/qwt_plot_spectrocurve.cpp \
        $$QWT_SRC/qwt_plot_scaleitem.cpp \
        $$QWT_SRC/qwt_plot_legenditem.cpp \
        $$QWT_SRC/qwt_plot_seriesitem.cpp \
        $$QWT_SRC/qwt_plot_shapeitem.cpp \
        $$QWT_SRC/qwt_plot_marker.cpp \
        $$QWT_SRC/qwt_plot_textlabel.cpp \
        $$QWT_SRC/qwt_plot_layout.cpp \
        $$QWT_SRC/qwt_plot_canvas.cpp \
        $$QWT_SRC/qwt_plot_panner.cpp \
        $$QWT_SRC/qwt_plot_rasteritem.cpp \
        $$QWT_SRC/qwt_plot_picker.cpp \
        $$QWT_SRC/qwt_plot_zoomer.cpp \
        $$QWT_SRC/qwt_plot_magnifier.cpp \
        $$QWT_SRC/qwt_plot_rescaler.cpp \
        $$QWT_SRC/qwt_point_mapper.cpp \
        $$QWT_SRC/qwt_raster_data.cpp \
        $$QWT_SRC/qwt_matrix_raster_data.cpp \
        $$QWT_SRC/qwt_sampling_thread.cpp \
        $$QWT_SRC/qwt_series_data.cpp \
        $$QWT_SRC/qwt_point_data.cpp \
        $$QWT_SRC/qwt_scale_widget.cpp
}

greaterThan(QT_MAJOR_VERSION, 4) {

    QT += printsupport
    QT += concurrent
}

contains(QWT_CONFIG, QwtSvg) {

    QT += svg

    HEADERS += $$QWT_SRC/qwt_plot_svgitem.h
    SOURCES += $$QWT_SRC/qwt_plot_svgitem.cpp
}
else {

    DEFINES += QWT_NO_SVG
}

contains(QWT_CONFIG, QwtOpenGL) {

    QT += opengl

    HEADERS += $$QWT_SRC/qwt_plot_glcanvas.h
    SOURCES += $$QWT_SRC/qwt_plot_glcanvas.cpp
}
else {

    DEFINES += QWT_NO_OPENGL
}

contains(QWT_CONFIG, QwtWidgets) {

    HEADERS += \
        $$QWT_SRC/qwt_abstract_slider.h \
        $$QWT_SRC/qwt_abstract_scale.h \
        $$QWT_SRC/qwt_arrow_button.h \
        $$QWT_SRC/qwt_analog_clock.h \
        $$QWT_SRC/qwt_compass.h \
        $$QWT_SRC/qwt_compass_rose.h \
        $$QWT_SRC/qwt_counter.h \
        $$QWT_SRC/qwt_dial.h \
        $$QWT_SRC/qwt_dial_needle.h \
        $$QWT_SRC/qwt_knob.h \
        $$QWT_SRC/qwt_slider.h \
        $$QWT_SRC/qwt_thermo.h \
        $$QWT_SRC/qwt_wheel.h

    SOURCES += \
        $$QWT_SRC/qwt_abstract_slider.cpp \
        $$QWT_SRC/qwt_abstract_scale.cpp \
        $$QWT_SRC/qwt_arrow_button.cpp \
        $$QWT_SRC/qwt_analog_clock.cpp \
        $$QWT_SRC/qwt_compass.cpp \
        $$QWT_SRC/qwt_compass_rose.cpp \
        $$QWT_SRC/qwt_counter.cpp \
        $$QWT_SRC/qwt_dial.cpp \
        $$QWT_SRC/qwt_dial_needle.cpp \
        $$QWT_SRC/qwt_knob.cpp \
        $$QWT_SRC/qwt_slider.cpp \
        $$QWT_SRC/qwt_thermo.cpp \
        $$QWT_SRC/qwt_wheel.cpp
}
