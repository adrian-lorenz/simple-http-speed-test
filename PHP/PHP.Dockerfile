FROM php:fpm
RUN apt-get update && apt-get install -y --no-install-recommends \
    libfreetype6-dev \
    libicu-dev \
    libjpeg-dev \
    libmagickwand-dev \
    libpng-dev \
    libwebp-dev \
    libzip-dev \
    && docker-php-ext-install -j "$(nproc)" \
    pdo \
    pdo_mysql \
    mysqli \
    bcmath \
    exif \
    gd \
    intl \
    zip \
    && docker-php-ext-configure gd --with-freetype --with-jpeg --with-webp \
    && pecl install xdebug \
    && docker-php-ext-enable xdebug



RUN set -eux; \
    docker-php-ext-enable opcache; \
    { \
    echo 'opcache.memory_consumption=256'; \
    echo 'opcache.interned_strings_buffer=16'; \
    echo 'opcache.max_accelerated_files=10000'; \
    echo 'opcache.revalidate_freq=0'; \
    echo 'opcache.fast_shutdown=1'; \
    } > /usr/local/etc/php/conf.d/opcache-recommended.ini


# FPM Konfiguration optimieren
RUN { \
    echo '[global]'; \
    echo 'daemonize = no'; \
    echo '[www]'; \
    echo 'listen = 9000'; \
    echo 'pm = dynamic'; \
    echo 'pm.max_children = 50'; \
    echo 'pm.start_servers = 10'; \
    echo 'pm.min_spare_servers = 5'; \
    echo 'pm.max_spare_servers = 10'; \
    echo 'pm.max_requests = 500'; \
    echo 'catch_workers_output = yes'; \
} > /usr/local/etc/php-fpm.d/zz-docker.conf

